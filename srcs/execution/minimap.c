/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:03:39 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/29 17:04:04 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	draw_map(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
// {
// 	int			dim;
// 	mlx_image_t	*block;

// 	dim = 80;
// 	block = mlx_new_image(mlx, dim, dim);
	
// 	while (y < cub3d->map.rows)
// 	{
// 		while (x < cub3d->map.cols)
// 		{
// 			if (cub3d->map.grid[y][x] == '1')
// 				// something
// 			else if (cub3d->map.grid[y][x] == '0' || cub3d->map.grid[y][x] == 'N' || cub3d->map.grid[y][x] == 'S' || cub3d->map.grid[y][x] == 'W' || cub3d->map.grid[y][x] == 'E')
// 				// something
// 			x++;
// 		}
// 		y++;
// 		x = 0;
// 	}
// }

static void	draw_blocks(t_cub3d *cub3d, mlx_t *mlx)
{
	int			dim;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	int x;
	int y;

	x = 0;
	y = 0;
	dim = 50;

	// Making images
	wall = mlx_new_image(mlx, dim, dim);
	while (y < dim)
	{
		while (x < dim)
		{
			if (x == 0 || x == dim - 1 || y == 0 || y == dim - 1) 
				mlx_put_pixel(wall, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(wall, x, y, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}

	x = 0;
	y = 0;
	floor = mlx_new_image(mlx, dim, dim);
	while (y < dim)
	{
		while (x < dim)
		{
			if (x == 0 || x == dim - 1 || y == 0 || y == dim - 1) 
				mlx_put_pixel(floor, x, y, 0x000000FF);
			else
				mlx_put_pixel(floor, x, y, 0xFFFFFFFF);
			x++;
		}
		x = 0;
		y++;
	}

	x = 0;
	y = 0;
	player = mlx_new_image(mlx, dim / 2, dim / 2);
	while (y < dim / 2)
	{
		while (x < dim / 2)
		{
			mlx_put_pixel(player, x, y, 0x00FF00FF);
			x++;
		}
		x = 0;
		y++;
	}

	// Drawing map
	x = 0;
	y = 0;
	while (y < cub3d->map.rows)
	{
		while (x < cub3d->map.cols)
		{
			if (cub3d->map.grid[y][x] == '1')
				mlx_image_to_window(mlx, wall, x * dim, y * dim);
			else if (cub3d->map.grid[y][x] == '0' || cub3d->map.grid[y][x] == 'N' || cub3d->map.grid[y][x] == 'S' || cub3d->map.grid[y][x] == 'W' || cub3d->map.grid[y][x] == 'E')
				mlx_image_to_window(mlx, floor, x * dim, y * dim);
			x++;
		}
		y++;
		x = 0;
	}
	
	// Drawing player
	x = 0;
	y = 0;
	while (y < cub3d->map.rows)
	{
		while (x < cub3d->map.cols)
		{
			if (cub3d->map.grid[y][x] == 'N' || cub3d->map.grid[y][x] == 'S' || cub3d->map.grid[y][x] == 'W' || cub3d->map.grid[y][x] == 'E')
				mlx_image_to_window(mlx, player, x * dim, y * dim); // needs to break out of all loops when found
			x++;
		}
		y++;
		x = 0;
	}
}

void	minimap(t_cub3d *cub3d)
{
	int	dimen;

	dimen = 0;
	dimen++;
	draw_blocks(cub3d, cub3d->mlx);
	// draw_map(cub3d, cub3d->mlx, 0, 0);
}