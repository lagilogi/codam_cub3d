/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:28:10 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/15 15:13:23 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_map_edge(t_cub3d *cub3d, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < rows)
	{
		while (x < cols)
		{
			if (cub3d->map.grid[0][x] == '0' || cub3d->map.grid[rows - 1][x] == '0')
				parsefile_error_handler(cub3d, 2);
			else if (cub3d->map.grid[y][0] == '0' || cub3d->map.grid[y][cols - 1] == '0')
				parsefile_error_handler(cub3d, 2);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	check_inner_map(t_cub3d *cub3d, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < rows)
	{
		while (x < cols)
		{
			if (check_char(cub3d->map.grid[y][x], 5))
			{
				if (!check_char(cub3d->map.grid[y + 1][x], 6) || !check_char(cub3d->map.grid[y - 1][x], 6) || !check_char(cub3d->map.grid[y][x + 1], 6) || !check_char(cub3d->map.grid[y][x - 1], 6))
					parsefile_error_handler(cub3d, 2);
			}
			x++;
		}
		x = 0;
		y++;
	}
	cub3d->player.delta_y = sin(cub3d->player.angle);
	cub3d->player.delta_x = cos(cub3d->player.angle);
	cub3d->player.plane_x = cos(cub3d->player.angle + PI / 2);
	cub3d->player.plane_y = sin(cub3d->player.angle + PI / 2);
}

static void	create_map_array(t_cub3d *cub3d)
{
	int	y;

	y = 0;
	cub3d->map.grid = malloc(cub3d->map.rows * sizeof(char *));
	if (cub3d->map.grid == NULL)
		parsefile_error_handler(cub3d, 4);
	while (y < cub3d->map.rows)
	{
		cub3d->map.grid[y] = malloc(cub3d->map.cols * sizeof(char));
		if (cub3d->map.grid[y] == NULL)
			clear_gnl(cub3d, 4, 2);
		y++;
	}
}

static void	copy_map_data(t_cub3d *cub3d, char *line, int y, int x)
{
	bool	eol;

	eol = false;
	while (x < cub3d->map.cols)
	{
		if (eol == false && (line[x] == '\n' || line[x] == '\0'))
			eol = true;
		if (eol == false)
		{
			cub3d->map.grid[y][x] = line[x];
				if (line[x] == 'N')
			cub3d->player.angle = 0.5 * PI;
				else if (line[x] == 'W')
			cub3d->player.angle = 2 * PI;
				else if (line[x] == 'S')
			cub3d->player.angle = 1.5 * PI;
				else if (line[x] == 'E')
			cub3d->player.angle = PI;
		}
		else
			cub3d->map.grid[y][x] = ' ';
		x++;
	}
}

void	parse_map(t_cub3d *cub3d)
{
	char	*line;
	int		y;

	y = 0;
	gnl_till_map(cub3d);
	create_map_array(cub3d);
	while (y < cub3d->map.rows)
	{
		line = get_next_line(cub3d->map_fd);
		if (line == NULL)
			parsefile_error_handler(cub3d, 4);
		copy_map_data(cub3d, line, y, 0);
		free(line);
		y++;
	}
	clear_gnl(cub3d, 0, 0);
	if (close(cub3d->map_fd) == -1)
		parsefile_error_handler(cub3d, 3);
	cub3d->map_fd = 0;
	check_map_edge(cub3d, cub3d->map.rows, cub3d->map.cols);
	check_inner_map(cub3d, cub3d->map.rows, cub3d->map.cols);
	if (close(cub3d->map_fd) == -1)
		parsefile_error_handler(cub3d, 3);
}
