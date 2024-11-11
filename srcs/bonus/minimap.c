/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:03:39 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/11 18:32:46 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// VERSION 1 -------

// static void	draw_map(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
// {
// 	int	px;
// 	int	py;

// 	while (y < cub3d->map.rows)
// 	{
// 		while (x < cub3d->map.cols)
// 		{
// 			if (cub3d->map.grid[y][x] == '1')
// 				if (mlx_image_to_window(mlx, cub3d->mini.w, x * DIM, y * DIM) == -1)
// 					execution_error_handler(cub3d, 3);
// 			if (check_char(cub3d->map.grid[y][x], 5))
// 				if (mlx_image_to_window(mlx, cub3d->mini.f, x * DIM, y * DIM) == -1)
// 					execution_error_handler(cub3d, 3);
// 			x++;
// 		}
// 		y++;
// 		x = 0;
// 	}
// 	px = DIM * (cub3d->player.x - 0.25);
// 	py = DIM * (cub3d->player.y - 0.25);
// 	if (mlx_image_to_window(mlx, cub3d->mini.p, px, py) == -1)
// 		execution_error_handler(cub3d, 3);
// }

// static void	draw_player(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
// {
// 	cub3d->mini.p = mlx_new_image(mlx, DIM / 2, DIM / 2);
// 	if (cub3d->mini.p == NULL)
// 		execution_error_handler(cub3d, 2);
// 	while (y < DIM / 2)
// 	{
// 		while (x < DIM / 2)
// 		{
// 			mlx_put_pixel(cub3d->mini.p, x, y, 0x00FF00FF);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	cub3d->player.delta_y = sin(cub3d->player.angle);
// 	cub3d->player.delta_x = cos(cub3d->player.angle);
// }

// static void	draw_wall(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
// {
// 	cub3d->mini.w = mlx_new_image(mlx, DIM, DIM);
// 	if (cub3d->mini.w == NULL)
// 		execution_error_handler(cub3d, 2);
// 	while (y < DIM)
// 	{
// 		while (x < DIM)
// 		{
// 			mlx_put_pixel(cub3d->mini.w, x, y, 0x000000FF);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }

// static void	draw_floor(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
// {
// 	cub3d->mini.f = mlx_new_image(mlx, DIM, DIM);
// 	if (cub3d->mini.f == NULL)
// 		execution_error_handler(cub3d, 2);
// 	while (y < DIM)
// 	{
// 		while (x < DIM)
// 		{
// 			if (x == 0 || x == DIM - 1 || y == 0 || y == DIM - 1) 
// 				mlx_put_pixel(cub3d->mini.f, x, y, 0xdfdfdfFF);
// 			else
// 				mlx_put_pixel(cub3d->mini.f, x, y, 0xFFFFFFFF);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }

// void	draw_minimap(t_cub3d *cub3d, int width, int height)
// {
// 	int	y;
// 	int	x;
	
// 	cub3d->mini.map = mlx_new_image(cub3d->mlx, DIM * width, DIM * height);
// 	if (cub3d->mini.map == NULL)
// 		execution_error_handler(cub3d, 2);
// 	while (y < DIM * height)
// 	{
// 		while (x < DIM * width)
// 		{
			
// 			if (cub3d->map.grid[(int)y/DIM][(int)x/DIM] == '0')
// 				mlx_put_pixel(cub3d->mini.f, x, y, 0xFFFFFFFF);
// 			if (cub3d->map.grid[(int)y/DIM][(int)x/DIM] == '1')
// 				mlx_put_pixel(cub3d->mini.f, x, y, 0x000000FF);
// 			y++;
// 		}
// 		x = 0;
// 	}
// }

// void	create_minimap(t_cub3d *cub3d)
// {
	// draw_floor(cub3d, cub3d->mlx, 0, 0);
	// draw_wall(cub3d, cub3d->mlx, 0, 0);
	// draw_player(cub3d, cub3d->mlx, 0, 0);
	// draw_map(cub3d, cub3d->mlx, 0, 0);
// 	printf("POS y: %f, x: %f, Dy: %f, Dx: %f, angle: %f\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle);
// }





// VERSION 2 -----------

void	draw_player(t_cub3d *cub3d, mlx_t *mlx, int x, int y)
{
	if (cub3d->mini.p != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->mini.p);
	cub3d->mini.p = mlx_new_image(mlx, DIM / 2, DIM / 2);
	if (cub3d->mini.p == NULL)
		execution_error_handler(cub3d, 2);
	while (y < DIM / 2)
	{
		while (x < DIM / 2)
		{
			mlx_put_pixel(cub3d->mini.p, x, y, 0x00FF00FF);
			x++;
		}
		x = 0;
		y++;
	}
	x = DIM * (cub3d->player.x - 0.25);
	y = DIM * (cub3d->player.y - 0.25);
	if (mlx_image_to_window(cub3d->mlx, cub3d->mini.p, x, y) == -1)
		execution_error_handler(cub3d, 3);
}

void	draw_minimap(t_cub3d *cub3d, int width, int height)
{
	int	y;
	int	x;
	
	y = 0;
	x = 0;
	cub3d->mini.map = mlx_new_image(cub3d->mlx, DIM * width, DIM * height);
	if (cub3d->mini.map == NULL)
		execution_error_handler(cub3d, 2);
	while (y < DIM * height)
	{
		while (x < DIM * width)
		{
			if (check_char(cub3d->map.grid[(int)y/DIM][(int)x/DIM], 5))
				mlx_put_pixel(cub3d->mini.map, x, y, 0xFFFFFFFF);
			if (cub3d->map.grid[(int)y/DIM][(int)x/DIM] == '1')
				mlx_put_pixel(cub3d->mini.map, x, y, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->mini.map, 0, 0) == -1)
		execution_error_handler(cub3d, 3);
}

void	create_minimap(t_cub3d *cub3d)
{
	draw_minimap(cub3d, cub3d->map.cols, cub3d->map.rows);
	draw_player(cub3d, cub3d->mlx, 0, 0);
	printf("POS y: %f, x: %f, Dy: %f, Dx: %f, angle: %f\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle);
}
