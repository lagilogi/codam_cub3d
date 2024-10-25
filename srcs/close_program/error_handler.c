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
		write(2, "ERROR: Couldn't load texture\n", 30);
	else if (i == 2)
		write(2, "ERROR: Invalid map\n", 20);
	else if (i == 3)
		write(2, "ERROR: couldn't close map_fd\n", 30);
	else if (i == 4)
		write(2, "ERROR: Parse_file failed malloc\n", 33);
	close_program(cub3d, NULL, 1);
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
		write(2, "ERROR: invalid map\n", 20);
	else if (i == 5)
		write(2, "ERROR: Invalid identifier in file\n", 35);
	else if (i == 6)
		write(2, "ERROR: Missing map information\n", 32);
	else if (i == 7)
		write(2, "ERROR: Invalid map size\n", 25);
	else if (i == 8)
		write(2, "ERROR: invalid player amount\n", 30);
	else if (i == 9)
		write(2, "ERROR: couldn't close map_fd\n", 30);
	else if (i == 10)
		write(2, "ERROR: check_file failed malloc\n", 33);
	close_program(NULL, NULL, 1);
}

void	error_handler(int i)
{
	if (i == 1)
		write(2, "ERROR: Too many arguments\n", 27);
	else if (i == 2)
		write(2, "ERROR: Incorrect file type\n", 28);
	else if (i == 3)
		write(2, "ERROR: Couldn't open file\n", 27);
	close_program(NULL, NULL, 1);
}
