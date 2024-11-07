/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   user_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:30:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/07 20:03:06 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_forward(t_cub3d *cub3d)
{
	cub3d->player.y -= cub3d->player.delta_y;
	cub3d->player.x -= cub3d->player.delta_x;
	cub3d->mini.p->instances[0].y -= cub3d->player.delta_y;
	cub3d->mini.p->instances[0].x -= cub3d->player.delta_x;
}

static void	ft_backward(t_cub3d *cub3d)
{
	cub3d->player.y += cub3d->player.delta_y;
	cub3d->player.x += cub3d->player.delta_x;
	cub3d->mini.p->instances[0].y += cub3d->player.delta_y;
	cub3d->mini.p->instances[0].x += cub3d->player.delta_x;
}

static void	ft_move_left(t_cub3d *cub3d)
{
	cub3d->mini.p->instances[0].x -= 0.1 * DIM;
	cub3d->player.x -= 0.1;
}

static void	ft_move_right(t_cub3d *cub3d)
{
	cub3d->mini.p->instances[0].x += 0.1 * DIM;
	cub3d->player.x += 0.1;
}

void ft_turn_left(t_cub3d *cub3d)
{
	cub3d->player.angle -= 0.1;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * PI;
	cub3d->player.delta_x = cos(cub3d->player.angle) * 5;
	cub3d->player.delta_y = sin(cub3d->player.angle) * 5;
}

void ft_turn_right(t_cub3d *cub3d)
{
	cub3d->player.angle += 0.1;
	if (cub3d->player.angle > 2 * PI)
		cub3d->player.angle -= 2 * PI;
	cub3d->player.delta_x = cos(cub3d->player.angle) * 5;
	cub3d->player.delta_y = sin(cub3d->player.angle) * 5;
}

void	user_input(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;
	int		y;
	int		x;

	cub3d = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_program(cub3d, 0);
	y = cub3d->player.y;
	x = cub3d->player.x;
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
	printf("POS y: %.2f, x: %.2f, Dy: %.2f, Dx: %.2f, angle: %.2f, degrees: %.2f, COORDS y: %d, x: %d\n", cub3d->player.y, cub3d->player.x, cub3d->player.delta_y, cub3d->player.delta_x, cub3d->player.angle, cub3d->player.angle * (180/PI), cub3d->mini.p->instances[0].y, cub3d->mini.p->instances[0].x);
	// printf("angle: %.2f, degrees: %.2f, COORDS y: %d, x: %d\n", cub3d->player.angle, cub3d->player.angle * (180/PI), cub3d->mini.p->instances[0].y, cub3d->mini.p->instances[0].x);

}
