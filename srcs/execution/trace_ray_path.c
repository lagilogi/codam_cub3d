/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:11:32 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/19 16:22:13 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	handle_walls(t_cub3d *cub3d, t_raycast *cast)
{
	if (cast->map_y > cub3d->map.rows || cast->map_x > cub3d->map.cols || \
		cast->map_y < 0 || cast->map_x < 0)
		return (true);
	if (cub3d->map.grid[cast->map_y][cast->map_x] == 'D')
	{
		cast->texture = cub3d->map.closed_door;
		return (true);
	}
	if (cub3d->map.grid[cast->map_y][cast->map_x] == 'd')
	{
		cast->open_door = true;
		return (false);
	}
	cast->open_door = false;
	return (false);
}

void	trace_ray_path(t_cub3d *cub3d, t_raycast *cast)
{
	while (1)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side_hit = vertical;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side_hit = horizontal;
		}
		if (cub3d->map.grid[cast->map_y][cast->map_x] == '1')
		{
			if (cast->open_door == true)
				cast->texture = cub3d->map.open_door;
			cast->open_door = false;
			break ;
		}
		if (handle_walls(cub3d, cast) == true)
			break ;
	}
}

void	render_sides_door_in_door(t_cub3d *cub3d, t_raycast *cast)
{
	if (cub3d->map.grid[(int)cub3d->player.y][(int)cub3d->player.x] == 'd')
	{
		if (cast->side_hit == vertical)
		{
			if (cast->step_x == -1 && cast->map_y == (int)cub3d->player.y \
			&& cast->map_x + 1 == (int)cub3d->player.x)
				cast->texture = cub3d->map.open_door;
			else if (cast->step_x == 1 && cast->map_y == (int)cub3d->player.y \
			&& cast->map_x - 1 == (int)cub3d->player.x)
				cast->texture = cub3d->map.open_door;
		}
		else
		{
			if (cast->step_y == -1 && cast->map_x == (int)cub3d->player.x \
			&& cast->map_y + 1 == (int)cub3d->player.y)
				cast->texture = cub3d->map.open_door;
			else if (cast->step_y == 1 && cast->map_x == (int)cub3d->player.x \
			&& cast->map_y - 1 == (int)cub3d->player.y)
				cast->texture = cub3d->map.open_door;
		}
	}
}
