/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:49:45 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/18 15:28:41 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clean_up_torches(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < N_TORCH_TXTRS)
	{
		if (cub3d->torch_images[i] != NULL)
			mlx_delete_image(cub3d->mlx, cub3d->torch_images[i]);
		else
			break ;
		i++;
	}
	free(cub3d->torch_images);
}

static void	free_map_array(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->map.rows && cub3d->map.grid[i] != NULL)
	{
		free(cub3d->map.grid[i]);
		i++;
	}
	free (cub3d->map.grid);
}

static void	clean_up(t_cub3d *cub3d)
{
	if (cub3d->map_fd != 0 && close(cub3d->map_fd) == -1)
		write(2, "Failed closing map fd\n", 23);
	if (cub3d->map.no != NULL)
		mlx_delete_texture(cub3d->map.no);
	if (cub3d->map.so != NULL)
		mlx_delete_texture(cub3d->map.so);
	if (cub3d->map.we != NULL)
		mlx_delete_texture(cub3d->map.we);
	if (cub3d->map.ea != NULL)
		mlx_delete_texture(cub3d->map.ea);
	if (cub3d->map.grid != NULL)
		free_map_array(cub3d);
	if (cub3d->mini.map != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->mini.map);
	if (cub3d->map.walls != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->map.walls);
	if (cub3d->torch_images != NULL)
		clean_up_torches(cub3d);
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
}

void	close_program_wrapper(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	close_program(cub3d, 0);
}

void	close_program(t_cub3d *cub3d, int exit_code)
{
	if (cub3d == NULL)
		exit(exit_code);
	clean_up(cub3d);
	if (exit_code == 0)
		write(1, "Cub3d finished!\n", 17);
	exit(exit_code);
}
