/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_program.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 17:49:45 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 19:34:53 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_map_array(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->file.map_rows && cub3d->map.grid[i] != NULL)
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
	if (cub3d->map.NO != NULL)
		mlx_delete_texture(cub3d->map.NO);
	if (cub3d->map.SO != NULL)
		mlx_delete_texture(cub3d->map.SO);
	if (cub3d->map.WE != NULL)
		mlx_delete_texture(cub3d->map.WE);
	if (cub3d->map.EA != NULL)
		mlx_delete_texture(cub3d->map.EA);
	if (cub3d->map.grid != NULL)
		free_map_array(cub3d);
}

void	close_program(t_cub3d *cub3d, char *msg, int exit_code)
{
	if (cub3d == NULL)
		exit(exit_code);
	clean_up(cub3d);
	if (msg != NULL)
		write(2, msg, ft_strlen(msg));
	exit(exit_code);
}
