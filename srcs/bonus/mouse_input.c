/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:42:25 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/18 14:42:30 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
