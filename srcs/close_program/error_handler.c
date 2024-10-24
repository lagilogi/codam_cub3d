/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 17:09:11 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/24 19:30:52 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parsefile_error_handler(t_cub3d *cub3d, int i)
{
	if (i == 1)
		write(2, "ERROR: failed malloc\n", 22);
	if (i == 2)
		write(2, "ERROR: invalid texture line\n", 29);
	close_program(cub3d, NULL, 1);
}

void	checkfile_error_handler(t_cub3d *cub3d, int i)
{
	if (i == 1)
		write(2, "ERROR: invalid ground/ceiling color line\n", 42);
	if (i == 2)
		write(2, "ERROR: invalid texture line\n", 29);
	if (i == 3)
		write(2, "ERROR: invalid amount of required info\n", 42);
	if (i == 4)
		write(2, "ERROR: invalid map\n", 20);
	if (i == 5)
		write(2, "ERROR: Invalid identifier in file\n", 35);
	if (i == 6)
		write(2, "ERROR: Missing map information\n", 32);
	if (i == 7)
		write(2, "ERROR: Invalid map size\n", 25);
	if (i == 8)
		write(2, "ERROR: couldn't close map_fd\n", 30);
	close_program(cub3d, NULL, 1);
}

void	error_handler(int i)
{
	if (i == 1)
		write(2, "ERROR: Too many arguments\n", 27);
	if (i == 2)
		write(2, "ERROR: Incorrect file type\n", 28);
	if (i == 3)
		write(2, "ERROR: Couldn't open file\n", 26);
	close_program(NULL, NULL, 1);
}
