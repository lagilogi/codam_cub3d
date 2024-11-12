/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   user_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:30:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/08 16:27:19 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_forward(t_cub3d *cub3d)
{
	cub3d->player.y -= cub3d->player.delta_y * SPEED;
	cub3d->player.x -= cub3d->player.delta_x * SPEED;
}

static void	ft_backward(t_cub3d *cub3d)
{
	cub3d->player.y += cub3d->player.delta_y * SPEED;
	cub3d->player.x += cub3d->player.delta_x * SPEED;
}

static void	ft_move_left(t_cub3d *cub3d)
{
	cub3d->player.x -= cub3d->player.delta_y * SPEED;
	cub3d->player.y += cub3d->player.delta_x * SPEED;
}

static void	ft_move_right(t_cub3d *cub3d)
{
	cub3d->player.x += cub3d->player.delta_y * SPEED;
	cub3d->player.y -= cub3d->player.delta_x * SPEED;
}

void ft_turn_left(t_cub3d *cub3d)
{
	cub3d->player.angle -= 0.1;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * PI;
	cub3d->player.delta_x = sin(cub3d->player.angle);
	cub3d->player.delta_y = cos(cub3d->player.angle);
	cub3d->player.plane_x = -0.57735 * sin(cub3d->player.angle);
	cub3d->player.plane_y = 0.57735 * cos(cub3d->player.angle);
}

void ft_turn_right(t_cub3d *cub3d)
{
	cub3d->player.angle += 0.1;
	if (cub3d->player.angle > 2 * PI)
		cub3d->player.angle -= 2 * PI;
	cub3d->player.delta_x = sin(cub3d->player.angle);
	cub3d->player.delta_y = cos(cub3d->player.angle);
	cub3d->player.plane_x = -0.57735 * sin(cub3d->player.angle);
	cub3d->player.plane_y = 0.57735 * cos(cub3d->player.angle);
}

void	user_input(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_program(cub3d, 0);
	// y = cub3d->player.y;
	// x = cub3d->player.x;
	if (keydata.key == MLX_KEY_W)
		ft_forward(cub3d);
	else if (keydata.key == MLX_KEY_S)
		ft_backward(cub3d);
	else if (keydata.key == MLX_KEY_A)
		ft_move_left(cub3d);
	else if (keydata.key == MLX_KEY_D)
		ft_move_right(cub3d);
	else if (keydata.key == MLX_KEY_LEFT)
		ft_turn_left(cub3d);
	else if (keydata.key == MLX_KEY_RIGHT)
		ft_turn_right(cub3d);
	// cub3d->player.moved = true;
	redraw_player(cub3d, cub3d->mlx, 0, 0);
	printf("POS y: %.2f, x: %.2f, Dy: %.2f, Dx: %.2f, angle: %.2f, degrees: %.2f\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle, cub3d->player.angle * (180/PI));
}
