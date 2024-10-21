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

void	close_program(t_cub3d *cub3d, char *msg, int exit_code)
{
	if (close(cub3d->map_fd) == -1)
		write(2, "Failed closing map fd\n", 23);
	if (msg != NULL)
		write(2, msg, ft_strlen(msg));
	exit(exit_code);
}
