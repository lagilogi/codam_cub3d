/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:30:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/29 13:34:14 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// static void	ft_up(t_cub3d *cub3d)
// {
// 	cub3d->img.p->instances[0].y -= IMGH;
// 	cub3d->img.p2->instances[0].y -= IMGH;
// }

// static void	ft_down(t_cub3d *cub3d)
// {
// 	cub3d->img.p->instances[0].y += IMGH;
// 	cub3d->img.p2->instances[0].y += IMGH;
// }

// static void	ft_left(t_cub3d *cub3d)
// {
// 	cub3d->img.p->instances[0].x -= IMGW;
// 	cub3d->img.p2->instances[0].x -= IMGW;
// }

// static void	ft_right(t_cub3d *cub3d)
// {
// 	cub3d->img.p->instances[0].x += IMGW;
// 	cub3d->img.p2->instances[0].x += IMGW;
// }

void	movement(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;
	int		y;
	int		x;

	cub3d = param;
	y = cub3d->player.y;
	x = cub3d->player.x;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_program(cub3d, 0);
	// else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	// {
	// 	if (cub3d->win == 0)
	// 	{
	// 		if (keydata.key == MLX_KEY_W && tile_check(cub3d, -1, 0) == 1)
	// 			ft_up(cub3d);
	// 		else if (keydata.key == MLX_KEY_S && tile_check(cub3d, 1, 0) == 1)
	// 			ft_down(cub3d);
	// 		else if (keydata.key == MLX_KEY_A && tile_check(cub3d, 0, -1) == 1)
	// 			ft_left(cub3d);
	// 		else if (keydata.key == MLX_KEY_D && tile_check(cub3d, 0, 1) == 1)
	// 			ft_right(cub3d);
	// 		if (x != cub3d->player.x || y != cub3d->player.y)
	// 			moves_count(cub3d);
	// 	}
	// }
}