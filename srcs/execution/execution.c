/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:15:43 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/19 15:11:03 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	window_initilization(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (cub3d->mlx == NULL)
		close_program(cub3d, 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	// mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
	cub3d->map.walls = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (cub3d->map.walls == NULL)
		close_program(cub3d, 1);
	mlx_image_to_window(cub3d->mlx, cub3d->map.walls, 0, 0);
	render_frame(cub3d);
}

void open_close_door(mlx_key_data_t keydata, void *param)
{
	t_cub3d *cub3d;
	t_raycast cast;
	
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		ft_bzero(&cast, sizeof(t_raycast));
		cub3d = (t_cub3d *)param;
		cast.x = WIDTH / 2;
		cast.map_x = (int)cub3d->player.x;
		cast.map_y = (int)cub3d->player.y;
		calc_rays(cub3d, &cast);
		calc_step_deltas_x(cub3d, &cast);
		calc_step_deltas_y(cub3d, &cast);
		trace_ray_path_open_door(cub3d, &cast);
		if (cub3d->map.grid[cast.map_y][cast.map_x] != 'D' && cub3d->map.grid[cast.map_y][cast.map_x] != 'd')
			return ;
		calc_wall_dist(cub3d, &cast);
		if (cast.wall_dist < 2)
		{
			if (cub3d->map.grid[cast.map_y][cast.map_x] == 'D')
			{
				printf("opening door\n");
				cub3d->map.grid[cast.map_y][cast.map_x] = 'd';
			}
			else
			{
				printf("closing door\n");
				cub3d->map.grid[cast.map_y][cast.map_x] = 'D';
			}
			cub3d->moving = true;
		}
	}
}

void	run_cub3d(t_cub3d *cub3d)
{
	mlx_loop_hook(cub3d->mlx, user_input, cub3d);
	mlx_loop_hook(cub3d->mlx, update_torch, cub3d);
	mlx_key_hook(cub3d->mlx, open_close_door, cub3d);
	mlx_close_hook(cub3d->mlx, &close_program_wrapper, cub3d);
	mlx_loop(cub3d->mlx);
}

void	starting_exec(t_cub3d *cub3d)
{
	cub3d->map.grid[6][4] = 'D'; // remove this
	cub3d->map.door_txtr = mlx_load_png("textures/wall.png");
	window_initilization(cub3d);
	load_torches(cub3d);
	create_minimap(cub3d, cub3d->mlx);
	run_cub3d(cub3d);
}
