/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: saleunin <saleunin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:03:39 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 18:30:30 by wsonepou      ########   odam.nl         */
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

static void	draw_rays_loop(t_cub3d *cub3d)
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

static void	draw_minimap(t_cub3d *cub3d, int y, int x)
{
	int	my;
	int	mx;


	my = cub3d->mini.my / DIM;
	mx = cub3d->mini.mx / DIM;
	if (x >= 150 && x <= 170 && y >= 150 && y <= 170)
		mlx_put_pixel(cub3d->mini.map, x, y, 0xd7ff33FF);
	else if (check_char(cub3d->map.grid[my][mx], 5))
		mlx_put_pixel(cub3d->mini.map, x, y, 0xFFFFFFFF);
	else if (cub3d->map.grid[my][mx] == '1')
		mlx_put_pixel(cub3d->mini.map, x, y, 0x000000FF);
	else
		mlx_put_pixel(cub3d->mini.map, x, y, 0x444444FF);
}

static void	draw_map_loop(t_cub3d *cub3d, int y, int x)
{

	cub3d->mini.my = (cub3d->player.y * DIM) - MAPSIZE / 2;
	while (y < MAPSIZE)
	{
		cub3d->mini.mx = (cub3d->player.x * DIM) - MAPSIZE / 2;
		while (x < MAPSIZE)
		{
			if (x < 3 || x > 316 || y < 3 || y > 316)
				mlx_put_pixel(cub3d->mini.map, x, y, 0x00FF00FF);
			else if (cub3d->mini.my < 0
				|| cub3d->mini.my >= cub3d->map.rows * DIM || cub3d->mini.mx < 0
				|| cub3d->mini.mx >= cub3d->map.cols * DIM)
				mlx_put_pixel(cub3d->mini.map, x, y, 0x444444FF);
			else
				draw_minimap(cub3d, y, x);
			x++;
			cub3d->mini.mx++;
		}
		x = 0;
		y++;
		cub3d->mini.my++;
	}
}

void	create_minimap(t_cub3d *cub3d, mlx_t *mlx)
{
	if (cub3d->mini.map)
		mlx_delete_image(mlx, cub3d->mini.map);
	cub3d->mini.map = mlx_new_image(mlx, 320, 320);
	if (cub3d->mini.map == NULL)
		execution_error_handler(cub3d, 2);
	draw_map_loop(cub3d, 0, 0);
	draw_rays_loop(cub3d);
	if (mlx_image_to_window(mlx, cub3d->mini.map, OFFSET, OFFSET) == -1)
		execution_error_handler(cub3d, 3);
}
