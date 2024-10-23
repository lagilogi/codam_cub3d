/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 17:09:11 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 18:07:06 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_file_error_handler(t_cub3d *cub3d, int i)
{
	return ;
}

void	error_handler(int i)
{
	if (i == 1)
	{
		write(2, "ERROR: Too many arguments\n", 20);
		exit(1);
	}
	if (i == 2)
	{
		write(2, "ERROR: Incorrect file type\n", 20);
		exit(2);
	}
	if (i == 3)
	{
		write(2, "ERROR: Couldn't open map\n", 20);
		exit(3);
	}
}
