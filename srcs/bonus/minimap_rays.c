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

static void	draw_minimap_ray(t_cub3d *cub3d, float ray_y, float ray_x, float angle)
{
	float	step_size;
	float	delta_y;
	float	delta_x;
	int		mini_x;
	int		mini_y;

	step_size = 0.05;
	delta_y = sin(angle);
	delta_x = cos(angle);
	mini_y = MAPSIZE / 2;
	mini_x = MAPSIZE / 2;
	while (1)
	{
		ray_y += delta_y * step_size;
		ray_x += delta_x * step_size;
		mini_y += delta_y * 2;
		mini_x += delta_x * 2;
		printf("%d %d  - %d %d\n", mini_y, mini_x, (int)ray_y, (int)ray_x);
		if (cub3d->map.grid[(int)ray_y][(int)ray_x] == '1')
			break ;
		if (!(mini_x >= 150 && mini_x <= 170 && mini_y >= 150 && mini_y <= 170))
			mlx_put_pixel(cub3d->mini.map, mini_x, mini_y, 0xFF0000FF);
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
		printf("\n[%d] \n", ray);
		ray_angle += (0.5 * PI) / MINIRAYS;
		draw_minimap_ray(cub3d, cub3d->player.y, cub3d->player.x, ray_angle);
		ray++;
	}
}
