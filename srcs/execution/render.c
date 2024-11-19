/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:42:56 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/19 16:17:00 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(
			t_raycast *cast, int start, int end, int color)
{
	const int	x = cast->x;
	int			y;

	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT;
	y = start;
	color += 255;
	while (y < end)
	{
		mlx_put_pixel(cast->img, x, y, color);
		++y;
	}
}

void	draw_vertical_line_texture(t_cub3d *cub3d, t_raycast *cast)
{
	const int	txtr_width = cast->texture->width;
	const int	txtr_height = cast->texture->height;
	int			index;
	uint32_t	color;
	int			y;

	if (cast->wall_top < 0 || cast->wall_bottom >= HEIGHT)
	{
		cast->wall_top = 0;
		cast->wall_bottom = HEIGHT;
	}
	y = cast->wall_top - 1;
	while (++y < cast->wall_bottom)
	{
		color = 0;
		index = (txtr_width * (int)cast->tex_y + (int)cast->tex_x) * 4;
		color += cast->texture->pixels[index] << 24;
		color += cast->texture->pixels[index + 1] << 16;
		color += cast->texture->pixels[index + 2] << 8;
		color += 255;
		cast->tex_y += cast->tex_step;
		if (cast->tex_y >= txtr_height)
			cast->tex_y = txtr_height - 1;
		mlx_put_pixel(cub3d->map.walls, cast->x, y, color);
	}
}

void	render_frame(t_cub3d *cub3d)
{
	t_raycast	cast;

	ft_bzero(&cast, sizeof(t_raycast));
	cast.img = cub3d->map.walls;
	while (cast.x < WIDTH)
	{
		cast.map_x = (int)cub3d->player.x;
		cast.map_y = (int)cub3d->player.y;
		calc_rays(cub3d, &cast);
		calc_step_deltas_x(cub3d, &cast);
		calc_step_deltas_y(cub3d, &cast);
		trace_ray_path(cub3d, &cast);
		calc_wall_dist(cub3d, &cast);
		render_sides_door_in_door(cub3d, &cast);
		calc_wall(cub3d, &cast);
		draw_vertical_line_texture(cub3d, &cast);
		draw_vertical_line(&cast, cast.wall_bottom, HEIGHT, cub3d->map.f_col);
		draw_vertical_line(&cast, 0, cast.wall_top, cub3d->map.c_col);
		cast.texture = NULL;
		++cast.x;
	}
}
