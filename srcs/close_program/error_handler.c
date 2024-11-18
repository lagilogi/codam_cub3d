/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:09:11 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/18 15:55:21 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	execution_error_handler(t_cub3d *cub3d, int i)
{
	if (i == 1)
		write(2, "ERROR: MLX failed initializing\n", 32);
	if (i == 2)
		write(2, "ERROR: failed creating minimap image\n", 38);
	if (i == 3)
		write(2, "ERROR: failed putting minimap image to window\n", 47);
	if (i == 4)
		write(2, "ERROR: failed drawing minimap rays\n", 36);
	close_program(cub3d, 1);
}

void	parsefile_error_handler(t_cub3d *cub3d, int i)
{
	if (i == 1)
		write(2, "ERROR: Couldn't load texture\n", 30);
	else if (i == 2)
		write(2, "ERROR: Invalid map\n", 20);
	else if (i == 3)
		write(2, "ERROR: couldn't close map_fd\n", 30);
	else if (i == 4)
		write(2, "ERROR: Parse_file failed malloc\n", 33);
	else if (i == 5)
		write(2, "ERROR: Door placement is invalid\n", 33);
	close_program(cub3d, 1);
}

void	checkfile_error_handler(int i)
{
	if (i == 1)
		write(2, "ERROR: invalid ground/ceiling color line\n", 42);
	else if (i == 2)
		write(2, "ERROR: invalid texture line\n", 29);
	else if (i == 3)
		write(2, "ERROR: invalid amount of required info\n", 40);
	else if (i == 4)
		write(2, "ERROR: invalid maps\n", 21);
	else if (i == 5)
		write(2, "ERROR: Invalid identifier in file\n", 35);
	else if (i == 6)
		write(2, "ERROR: Missing map information\n", 32);
	else if (i == 8)
		write(2, "ERROR: invalid player amount\n", 30);
	else if (i == 9)
		write(2, "ERROR: couldn't close map_fd\n", 30);
	else if (i == 10)
		write(2, "ERROR: empty file or failed malloc gnl\n", 40);
	close_program(NULL, 1);
}

void	error_handler(int i)
{
	if (i == 1)
		write(2, "ERROR: Invalid amount of arguments\n", 36);
	else if (i == 2)
		write(2, "ERROR: Incorrect file type\n", 28);
	else if (i == 3)
		write(2, "ERROR: Couldn't open file\n", 27);
	close_program(NULL, 1);
}
