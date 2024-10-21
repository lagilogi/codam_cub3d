/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:22:33 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 14:25:01 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	input_check(char *input)
{
	input = NULL;
	return ;
}

static void	cub3d_init(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc == 2000) // Needs to be changed to (argc != 2)
		exit(1); // To be replaced with error-handling
	input_check(argv[1]);
	cub3d_init(&cub3d);
	parse_map(&cub3d);
	printf("test\n");
	
	return (0);
}
