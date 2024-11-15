/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:22:33 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 16:44:11 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	input_check(t_cub3d *cub3d, char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i < 5)
		error_handler(2);
	if (input[i - 4] == '.' && input[i - 3] == 'c'
		&& input[i - 2] == 'u' && input[i - 1] == 'b')
	{
		cub3d->map_fd = open(input, O_RDONLY);
		if (cub3d->map_fd == -1)
			error_handler(3);
	}
	else
		error_handler(2);
}

static void	cub3d_init(t_cub3d *cub3d)
{
	ft_bzero(cub3d, sizeof(t_cub3d));
	ft_bzero(&cub3d->file, sizeof(t_file));
	ft_bzero(&cub3d->map, sizeof(t_map));
	ft_bzero(&cub3d->player, sizeof(t_player));
	ft_bzero(&cub3d->mini, sizeof(t_minimap));
	cub3d->moving = false;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		error_handler(1);
	cub3d_init(&cub3d);
	input_check(&cub3d, argv[1]);
	check_file(&cub3d, NULL, 0);
	parse_file(&cub3d, argv[1]);
	starting_exec(&cub3d);
	close_program(&cub3d, 0);
	return (0);
}
