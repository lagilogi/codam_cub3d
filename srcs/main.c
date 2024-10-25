/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:22:33 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/24 21:08:32 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_tester(t_cub3d *cub3d)
{
	int	x = 0, y = 0;
	
	printf("\n");
	printf("floor rgb: %d,%d,%d\n", cub3d->map.f_r, cub3d->map.f_g, cub3d->map.f_b);
	printf("ceiling rgb: %d,%d,%d\n", cub3d->map.c_r, cub3d->map.c_g, cub3d->map.c_b);

	printf("\n");

	printf("NORTH txtr Found\n");
	printf("SOUTH txtr Found\n");
	printf("WEST txtr Found\n");
	printf("EAST txtr Found\n");

	printf("\n");

	printf("player count: %d\n", cub3d->file.player_count);
	printf("player faces: %c\n", cub3d->player.facing);
	printf("player y: %d, x: %d\n", cub3d->player.y, cub3d->player.x);

	printf("\n");

	while (y < cub3d->file.map_rows)
	{
		while (x < cub3d->file.map_cols)
		{
			printf("%c", cub3d->map.grid[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

static void	input_check(t_cub3d *cub3d, char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i < 5)
		error_handler(2);
	if (input[i - 4] == '.' && input[i - 3] == 'c' && input[i - 2] == 'u' && input[i - 1] == 'b')
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
	parse_tester(&cub3d);
	close_program(&cub3d, NULL, 0);
	return (0);
}
