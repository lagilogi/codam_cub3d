/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_rays.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 17:38:17 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 19:30:43 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_mini_ray(t_cub3d *cub3d, float ray_y, float ray_x, float angle)
{
	float	delta_y;
	float	delta_x;
	int		map_x;
	int		map_y;

	delta_y = sin(angle);
	delta_x = cos(angle);
	map_y = MAPSIZE / 2;
	map_x = MAPSIZE / 2;
	while (map_x > 2 && map_x < MAPSIZE - 3 && map_y > 2 && map_y < MAPSIZE - 3)
	{
		ray_y -= delta_y * (1.0 / DIM);
		ray_x -= delta_x * (1.0 / DIM);
		map_y = (ray_y - cub3d->player.y) * DIM + (MAPSIZE / 2);
		map_x = (ray_x - cub3d->player.x) * DIM + (MAPSIZE / 2);
		if (cub3d->map.grid[(int)ray_y][(int)ray_x] == '1')
			break ;
		if (!(map_x >= 150 && map_x <= 170 && map_y >= 150 && map_y <= 170))
			mlx_put_pixel(cub3d->mini.map, map_x, map_y, 0xFF0000FF);
	}
}


void	draw_rays_loop(t_cub3d *cub3d)
{
	float	ray_angle;
	int		ray;
	
	ray = 0;
	ray_angle = cub3d->player.angle - 0.25 * PI;
	while (ray < MINIRAYS)
	{
		ray_angle += (0.5 * PI) / MINIRAYS;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		else if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		draw_mini_ray(cub3d, cub3d->player.y, cub3d->player.x, ray_angle);
		ray++;
	}
}
