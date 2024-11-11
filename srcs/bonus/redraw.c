/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redraw.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 14:54:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/08 16:21:29 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	redraw_player(t_cub3d *cub3d, mlx_t *mlx, int y, int x)
{
	int	px;
	int	py;
	
	if (cub3d->mini.p != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->mini.p);
	cub3d->mini.p = mlx_new_image(mlx, DIM / 2, DIM / 2);
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
	px = DIM * (cub3d->player.x - 0.25);
	py = DIM * (cub3d->player.y - 0.25);
	if (mlx_image_to_window(mlx, cub3d->mini.p, px, py) == -1)
		execution_error_handler(cub3d, 3);
}
