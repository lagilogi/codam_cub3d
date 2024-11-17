/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:30:05 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/15 16:07:14 by saleunin         ###   ########.fr       */
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

static void	ft_turn(t_cub3d *cub3d, int i)
{
	cub3d->moving = true;
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
	cub3d->player.plane_x = cos(cub3d->player.angle + PI / 2);
	cub3d->player.plane_y = sin(cub3d->player.angle + PI / 2);
}

void	handle_mouse(t_cub3d *cub3d)
{
	int	current_x;
	int	current_y;

	mlx_get_mouse_pos(cub3d->mlx, &current_x, &current_y);
	if (current_x != WIDTH / 2)
	{
		mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
		cub3d->player.angle += ((double)current_x - (WIDTH / 2)) / 30 * 0.05;
		if (cub3d->player.angle > 2 * PI)
			cub3d->player.angle -= 2 * PI;
		if (cub3d->player.angle < 2 * PI)
			cub3d->player.angle += 2 * PI;
		cub3d->player.delta_x = cos(cub3d->player.angle);
		cub3d->player.delta_y = sin(cub3d->player.angle);
		cub3d->player.plane_x = cos(cub3d->player.angle + PI / 2);
		cub3d->player.plane_y = sin(cub3d->player.angle + PI / 2);
		cub3d->moving = true;
	}
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void update_torch(t_cub3d *cub3d)
{
	static int i = 0;
	static long long last_frame;


	if (get_current_time() - last_frame < 100)
		return ;
	cub3d->torch_images[i]->instances->enabled = false;
	i++;
	if (i == N_TORCH_TXTRS)
		i = 0;
	cub3d->torch_images[i]->instances->enabled = true;
	last_frame = get_current_time();
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
	else if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		ft_turn(cub3d, 2);
	// else
	// 	handle_mouse(cub3d);
	if (cub3d->moving == true)
	{
		render_frame(cub3d);
		create_minimap(cub3d, cub3d->mlx);
	}
	cub3d->moving = false;
	update_torch(cub3d);
}
