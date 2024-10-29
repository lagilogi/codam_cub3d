/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 13:28:10 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/29 16:00:31 by wsonepou      ########   odam.nl         */
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
		{
			clear_gnl(cub3d, 4, 2);
		}
		y++;
	}
}

static void	copy_map_data(t_cub3d *cub3d, char *line, int y)
{
	int		x;
	bool	eol;

	x = 0;
	eol = false;
	while (x < cub3d->map.cols)
	{
		if (eol == false && (line[x] == '\n' || line[x] == '\0'))
			eol = true;
		if (eol == false)
			cub3d->map.grid[y][x] = line[x];
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
		copy_map_data(cub3d, line, y);
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
