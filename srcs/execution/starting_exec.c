/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starting_exec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:15:43 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/05 14:57:49 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	window_initilization(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (cub3d->mlx == NULL)
		close_program(cub3d, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->render_img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(cub3d->mlx, cub3d->render_img, 0, 0);

}

void	run_cub3d(t_cub3d *cub3d)
{
	// mlx_loop_hook(cub3d->mlx, &time_passage, cub3d);
	mlx_key_hook(cub3d->mlx, &user_input, cub3d);	
	mlx_loop(cub3d->mlx);
}


void	starting_exec(t_cub3d *cub3d)
{
	window_initilization(cub3d);
	
	create_minimap(cub3d);
	run_cub3d(cub3d);
}
