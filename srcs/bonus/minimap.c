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

static void	draw_border(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < MAPSIZE)
	{
		while (x < MAPSIZE)
		{
			if (x < 3 || x > 316 || y < 3 || y > 317)
				mlx_put_pixel(cub3d->mini.map, x, y, 0x00FF00FF);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	draw_minimap(t_cub3d *cub3d, int y, int x)
{
	int	my;
	int	mx;

	my = cub3d->mini.my / DIM;
	mx = cub3d->mini.mx / DIM;
	if (x < 3 || x > 316 || y < 3 || y > 316)
		return ;
	else if (cub3d->mini.mx < 0 || cub3d->mini.my < 0 || mx >= cub3d->map.cols)
		return ;
	if (x >= 150 && x <= 170 && y >= 150 && y <= 170)
		mlx_put_pixel(cub3d->mini.map, x, y, 0x00FF00FF);
	else if (check_char(cub3d->map.grid[my][mx], 5))
		mlx_put_pixel(cub3d->mini.map, x, y, 0xFFFFFFFF);
	else if (cub3d->map.grid[my][mx] == '1')
		mlx_put_pixel(cub3d->mini.map, x, y, 0x000000FF);
}

static void	draw_map_loop(t_cub3d *cub3d, int y, int x)
{
	int	my;

	cub3d->mini.my = (cub3d->player.y * DIM) - MAPSIZE / 2;
	while (y < MAPSIZE)
	{
		my = cub3d->mini.my / DIM;
		cub3d->mini.mx = (cub3d->player.x * DIM) - MAPSIZE / 2;
		while (x < MAPSIZE && my >= 0 && my < cub3d->map.rows)
		{
			draw_minimap(cub3d, y, x);
			x++;
			cub3d->mini.mx++;
			if (cub3d->mini.mx > cub3d->map.cols * DIM)
				break ;
		}
		x = 0;
		y++;
		cub3d->mini.my++;
		if (cub3d->mini.my > cub3d->map.rows * DIM)
			break ;
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
	draw_border(cub3d);
	if (mlx_image_to_window(mlx, cub3d->mini.map, OFFSET, OFFSET) == -1)
		execution_error_handler(cub3d, 3);
}
