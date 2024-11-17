/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:15:43 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/17 15:12:29 by saleunin         ###   ########.fr       */
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
	cub3d->map.walls = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (cub3d->map.walls == NULL)
		close_program(cub3d, 1);
	// mlx_image_to_window(cub3d->mlx, cub3d->map.walls, 0, 0);
	// mlx_texture_t *torch = mlx_load_png("textures/torch1.png");
	// if (torch == NULL)
	// 	close_program(cub3d, 1);
	// mlx_image_t *torch_img = mlx_texture_to_image(cub3d->mlx, torch);
	// mlx_image_to_window(cub3d->mlx, torch_img, WIDTH - 300, HEIGHT - 650);
}

void load_torches(t_cub3d *cub3d)
{
	mlx_texture_t *torch;
	char *tmp;
	char *str;
	int i;

	i = 1;
	cub3d->torch_images = malloc(sizeof(mlx_image_t *) * 6);
	if (!cub3d->torch_images)
		close_program(cub3d, 1);
	while (i - 1 < N_TORCH_TXTRS)
	{
		tmp = ft_itoa(i);
		str = ft_strjoin("textures/torch", tmp);
		free(tmp);
		tmp = ft_strjoin(str, ".png");
		free(str);
		torch = mlx_load_png(tmp);
		free(tmp);
		if (torch == NULL)
			close_program(cub3d, 1);
		cub3d->torch_images[i - 1] = mlx_texture_to_image(cub3d->mlx, torch);
		mlx_delete_texture(torch);
		if (cub3d->torch_images[i - 1] == NULL)
			close_program(cub3d, 1);
		mlx_image_to_window(cub3d->mlx, cub3d->torch_images[i - 1], WIDTH - 300, HEIGHT - 650);
		cub3d->torch_images[i - 1]->instances->enabled = false;
		i++;
	}
	cub3d->torch_images[i - 1] = NULL;
	cub3d->torch_images[0]->instances->enabled = true;
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
	load_torches(cub3d);
	create_minimap(cub3d, cub3d->mlx);
	run_cub3d(cub3d);
}
