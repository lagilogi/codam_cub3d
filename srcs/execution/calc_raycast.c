/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:09:56 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/18 14:44:54 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_rays(t_cub3d *cub3d, t_raycast *cast)
{
	const double	cam_x = 2 * cast->x / (double)WIDTH - 1;

	cast->ray_dir_x = -cub3d->player.delta_x + -cub3d->player.plane_x * cam_x;
	cast->ray_dir_y = -cub3d->player.delta_y + -cub3d->player.plane_y * cam_x;
}

void	calc_step_deltas_x(t_cub3d *cub3d, t_raycast *cast)
{
	cast->delta_dist_x = sqrt(1 + (cast->ray_dir_y * cast->ray_dir_y) / \
								(cast->ray_dir_x * cast->ray_dir_x));
	if (cast->ray_dir_x < 0)
	{
		cast->step_x = -1;
		cast->side_dist_x = (cub3d->player.x - cast->map_x) * \
													cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist_x = (cast->map_x + 1.0 - cub3d->player.x) * \
													cast->delta_dist_x;
	}
}

void	calc_step_deltas_y(t_cub3d *cub3d, t_raycast *cast)
{
	cast->delta_dist_y = sqrt(1 + \
	(cast->ray_dir_x * cast->ray_dir_x) / (cast->ray_dir_y * cast->ray_dir_y));
	if (cast->ray_dir_y < 0)
	{
		cast->step_y = -1;
		cast->side_dist_y = (cub3d->player.y - cast->map_y) * \
															cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist_y = (cast->map_y + 1.0 - cub3d->player.y) * \
															cast->delta_dist_y;
	}
}

void	calc_wall_dist(t_cub3d *cub3d, t_raycast *cast)
{
	if (cast->side_hit == vertical)
	{
		if (cast->step_x == -1)
			cast->texture = cub3d->map.ea;
		else
			cast->texture = cub3d->map.we;
		cast->wall_dist = (cast->map_x - cub3d->player.x + \
		(1 - cast->step_x) / 2) / cast->ray_dir_x;
	}
	else
	{
		if (cast->step_y == -1)
			cast->texture = cub3d->map.so;
		else
			cast->texture = cub3d->map.no;
		cast->wall_dist = (cast->map_y - cub3d->player.y + \
		(1 - cast->step_y) / 2) / cast->ray_dir_y;
	}
}

void	calc_wall(t_cub3d *cub3d, t_raycast *cast)
{
	cast->wall_height = (int)(HEIGHT / cast->wall_dist);
	cast->wall_top = -cast->wall_height / 2 + HEIGHT / 2;
	cast->wall_bottom = cast->wall_height / 2 + HEIGHT / 2;
	if (cast->side_hit == 0)
		cast->wall_x = cub3d->player.y + cast->wall_dist * cast->ray_dir_y;
	else
		cast->wall_x = cub3d->player.x + cast->wall_dist * cast->ray_dir_x;
	cast->wall_x -= floor((cast->wall_x));
	cast->tex_step = (double)cast->texture->height / \
				(cast->wall_bottom - cast->wall_top);
	if (cast->wall_bottom < HEIGHT)
		cast->tex_y = 0;
	else
		cast->tex_y = (cast->wall_bottom - HEIGHT) * cast->tex_step;
	cast->tex_x = (int)(cast->wall_x * cast->texture->width);
	if (cast->side_hit == 0 && cast->step_x < 0)
		cast->tex_x = cast->texture->width - cast->tex_x - 1;
	else if (cast->side_hit == 1 && cast->step_y > 0)
		cast->tex_x = cast->texture->width - cast->tex_x - 1;
	if (cast->tex_x >= cast->texture->width)
		cast->tex_x = cast->texture->width - 1;
}
