/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   user_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:30:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/11 18:32:28 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// VERSION 1 ------------------

static void	ft_move(t_cub3d *cub3d, char c)
{
	if (c == 'W' && !collision_check(cub3d, 'W'))
	{
		cub3d->player.y -= cub3d->player.delta_y * SPEED;
		cub3d->player.x -= cub3d->player.delta_x * SPEED;
	}
	else if (c == 'S' && !collision_check(cub3d, 'S'))
	{
		cub3d->player.y += cub3d->player.delta_y * SPEED;
		cub3d->player.x += cub3d->player.delta_x * SPEED;	
	}
	else if (c == 'A' && !collision_check(cub3d, 'A'))
	{
		cub3d->player.x -= cub3d->player.delta_y * SPEED;
		cub3d->player.y += cub3d->player.delta_x * SPEED;
	}
	else if (c == 'D' && !collision_check(cub3d, 'D'))
	{
		cub3d->player.x += cub3d->player.delta_y * SPEED;
		cub3d->player.y -= cub3d->player.delta_x * SPEED;
	}
}


static void ft_turn(t_cub3d *cub3d, int i)
{
	if (i == 1)
	{
		cub3d->player.angle -= 0.1;
		if (cub3d->player.angle < 0)
			cub3d->player.angle += 2 * PI;
		printf("LEFT!\n");
	}
	else
	{
		cub3d->player.angle += 0.1;
		if (cub3d->player.angle > 2 * PI)
			cub3d->player.angle -= 2 * PI;
		printf("RIGHT!\n");
	}
	cub3d->player.delta_x = cos(cub3d->player.angle);
	cub3d->player.delta_y = sin(cub3d->player.angle);
}

void	user_input(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		close_program(cub3d, 0);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		ft_move(cub3d, 'W');
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		ft_move(cub3d, 'S');
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		ft_move(cub3d, 'A');
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		ft_move(cub3d, 'D');
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		ft_turn(cub3d, 1);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		ft_turn(cub3d, 2);
	// cub3d->player.moved = true;
	draw_player(cub3d, cub3d->mlx, 0, 0);
	// printf("POS y: %.2f, x: %.2f, Dy: %.2f, Dx: %.2f, angle: %.2f, degrees: %.2f\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle, cub3d->player.angle * (180/PI));
}


// VERSION 2 ------------------

// static void	ft_forward_backward(t_cub3d *cub3d, char c)
// {
// 	float	y;
// 	float	x;

// 	if (c == 'W') // forward
// 	{
// 		y = cub3d->player.y - cub3d->player.delta_y * (SPEED * ACC);
// 		x = cub3d->player.x - cub3d->player.delta_x * (SPEED * ACC);
// 		if (cub3d->map.grid[(int)y][(int)x] == '1')
// 			return ;
// 		cub3d->player.y -= cub3d->player.delta_y * SPEED;
// 		cub3d->player.x -= cub3d->player.delta_x * SPEED;		
// 	}
// 	else if (c == 'S') // backward
// 	{
// 		y = cub3d->player.y + cub3d->player.delta_y * (SPEED * ACC);
// 		x = cub3d->player.x + cub3d->player.delta_x * (SPEED * ACC);
// 		if (cub3d->map.grid[(int)y][(int)x] == '1')
// 			return ;
// 		cub3d->player.y += cub3d->player.delta_y * SPEED;
// 		cub3d->player.x += cub3d->player.delta_x * SPEED;	
// 	}
// 	redraw_player(cub3d, cub3d->mlx, 0, 0);
// }

// static void	ft_left_right(t_cub3d *cub3d, char c)
// {
// 	float	y;
// 	float	x;

// 	if (c == 'A') // strafe left
// 	{
// 		x = cub3d->player.x - cub3d->player.delta_y * (SPEED * ACC);
// 		y = cub3d->player.y + cub3d->player.delta_x * (SPEED * ACC);
// 		if (cub3d->map.grid[(int)y][(int)x] == '1')
// 			return ;
// 		cub3d->player.x -= cub3d->player.delta_y * SPEED;
// 		cub3d->player.y += cub3d->player.delta_x * SPEED;
// 	}
// 	else if (c == 'D') // strafe right
// 	{
// 		x = cub3d->player.x + cub3d->player.delta_y * (SPEED * ACC);
// 		y = cub3d->player.y - cub3d->player.delta_x * (SPEED * ACC);
// 		if (cub3d->map.grid[(int)y][(int)x] == '1')
// 			return ;
// 		cub3d->player.x += cub3d->player.delta_y * SPEED;
// 		cub3d->player.y -= cub3d->player.delta_x * SPEED;
// 	}
// 	redraw_player(cub3d, cub3d->mlx, 0, 0);
// }

// void ft_turn(t_cub3d *cub3d, int i)
// {
// 	if (i == 1)
// 	{
// 		cub3d->player.angle -= 0.1;
// 		if (cub3d->player.angle < 0)
// 			cub3d->player.angle += 2 * PI;
// 	}
// 	else
// 	{
// 		cub3d->player.angle += 0.1;
// 		if (cub3d->player.angle > 2 * PI)
// 			cub3d->player.angle -= 2 * PI;
// 	}
// 	cub3d->player.delta_x = cos(cub3d->player.angle);
// 	cub3d->player.delta_y = sin(cub3d->player.angle);
// }

// void	user_input(mlx_key_data_t keydata, void *param)
// {
// 	t_cub3d	*cub3d;

// 	cub3d = param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		close_program(cub3d, 0);
// 	if (keydata.key == MLX_KEY_W)
// 		ft_forward_backward(cub3d, 'W');
// 	else if (keydata.key == MLX_KEY_S)
// 		ft_forward_backward(cub3d, 'S');
// 	else if (keydata.key == MLX_KEY_A)
// 		ft_left_right(cub3d, 'A');
// 	else if (keydata.key == MLX_KEY_D)
// 		ft_left_right(cub3d, 'D');
// 	else if (keydata.key == MLX_KEY_LEFT)
// 		ft_turn(cub3d, 1);
// 	else if (keydata.key == MLX_KEY_RIGHT)
// 		ft_turn(cub3d, 2);
// 	// cub3d->player.moved = true;
// 	redraw_player(cub3d, cub3d->mlx, 0, 0);
// 	printf("POS y: %.2f, x: %.2f, Dy: %.2f, Dx: %.2f, angle: %.2f, degrees: %.2f\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle, cub3d->player.angle * (180/PI));
// }








// VERSION 3 ------------------

// static void	ft_move(t_cub3d *cub3d, float y, float x, int i)
// {
// 	if (i == 1) // forward
// 	{
// 		y -= cub3d->player.y - cub3d->player.delta_y * (SPEED * 1.2);
// 		x -= cub3d->player.x - cub3d->player.delta_x * (SPEED * 1.2);
// 		collision_check(cub3d, y, x);
// 	}
// 	else if (i == 2) // backward
// 	{
// 		y += cub3d->player.y + cub3d->player.delta_y * (SPEED * 1.2);
// 		x += cub3d->player.x + cub3d->player.delta_x * (SPEED * 1.2);	
// 	}
// 	else if (i == 3) // strafe left
// 	{
// 		x -= cub3d->player.x - cub3d->player.delta_y * (SPEED * 1.2);
// 		y += cub3d->player.y + cub3d->player.delta_x * (SPEED * 1.2);
// 	}
// 	else if (i == 4) // strafe right
// 	{
// 		x += cub3d->player.x + cub3d->player.delta_y * (SPEED * 1.2);
// 		y -= cub3d->player.y - cub3d->player.delta_x * (SPEED * 1.2);
// 	}
// }