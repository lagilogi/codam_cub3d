/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: saleunin <saleunin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:15:43 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 18:07:44 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	window_initilization(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (cub3d->mlx == NULL)
		close_program(cub3d, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
	cub3d->map.walls = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (cub3d->map.walls == NULL)
		close_program(cub3d, 1);
	mlx_image_to_window(cub3d->mlx, cub3d->map.walls, 0, 0);
	render_frame(cub3d);
}

void	run_cub3d(t_cub3d *cub3d)
{
	mlx_loop_hook(cub3d->mlx, user_input, cub3d);
	mlx_close_hook(cub3d->mlx, &close_program_wrapper, cub3d);
	mlx_loop(cub3d->mlx);
}


void	starting_exec(t_cub3d *cub3d)
{
	window_initilization(cub3d);
	create_minimap(cub3d, cub3d->mlx);
	run_cub3d(cub3d);
}
