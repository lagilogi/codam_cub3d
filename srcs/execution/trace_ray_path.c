/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:11:32 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/19 15:59:14 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (cast->map_y > cub3d->map.rows || cast->map_x > cub3d->map.cols || \
			cast->map_y < 0 || cast->map_x < 0)
			break ;
		if (cub3d->map.grid[cast->map_y][cast->map_x] == 'D')
		{
			cast->texture = cub3d->map.closed_door;
			break ;
		}
		if (cub3d->map.grid[cast->map_y][cast->map_x] == 'd')
		{
			cast->open_door = true;
			continue ;
		}
		if (cast->open_door == true && cub3d->map.grid[cast->map_y][cast->map_x] == '1')
		{
			if ((cast->side_hit == vertical && cast->step_x == -1) || (cast->side_hit == horizontal && cast->step_y == -1))
			{
				cast->texture = cub3d->map.open_door;
				cast->open_door = false;
			}
			break ;
		}
		if (cub3d->map.grid[cast->map_y][cast->map_x] == '1')
			break ;
		cast->open_door = false;
	}
}

void	trace_ray_path_open_door(t_cub3d *cub3d, t_raycast *cast)
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
		if (cast->map_y > cub3d->map.rows || cast->map_x > cub3d->map.cols || \
			cast->map_y < 0 || cast->map_x < 0)
			break ;
		if (cub3d->map.grid[cast->map_y][cast->map_x] == 'D')
			break ;
		if (cub3d->map.grid[cast->map_y][cast->map_x] == 'd')
			break ;
		if (cub3d->map.grid[cast->map_y][cast->map_x] == '1')
			break ;
	}
}
