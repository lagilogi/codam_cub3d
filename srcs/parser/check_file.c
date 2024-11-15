/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:26:13 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 16:45:13 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_map(t_cub3d *cub3d, char *str, int i)
{
	int	map_size;

	map_size = 0;
	if (cub3d->file.data_c != 6)
		return (3);
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		{
			cub3d->file.player_count++;
			cub3d->player.y = cub3d->map.rows + 0.5;
			cub3d->player.x = i + 0.5;
		}
		if (check_char(str[i], 7) == 0)
			return (4);
		else
			map_size++;
		i++;
	}
	if (cub3d->map.cols < map_size)
		cub3d->map.cols = map_size;
	cub3d->map.rows++;
	return (0);
}

static int	check_texture(t_cub3d *cub3d, char *line, int i)
{
	if (!check_whitespace(line[2]))
		return (2);
	if (check_identifier(cub3d, line))
		return (3);
	while (check_whitespace(line[i]))
		i++;
	if (line[i] == '\n')
		return (2);
	cub3d->file.data_c++;
	return (0);
}

static int	check_colors(t_cub3d *cub3d, char *line)
{
	if (!check_whitespace(line[1]))
		return (1);
	if (check_identifier(cub3d, line) > 0)
		return (3);
	if (line[0] == 'F')
		if (get_floor_color(cub3d, line, 1) == 1)
			return (1);
	if (line[0] == 'C')
		if (get_ceiling_color(cub3d, line, 1) == 1)
			return (1);
	cub3d->file.data_c++;
	return (0);
}

static int	check_line(t_cub3d *cub3d, char *line, int i)
{
	while (line[i] && check_whitespace(line[i]))
		i++;
	if ((cub3d->file.after_map == true && (line[i] != '\n' || line[i] != '\0'))
		|| (cub3d->file.data_c == 6 && line[i] != '\n' && line[i] != '1'))
		return (4);
	else if (line[i] == 'F' || line[i] == 'C')
		return (check_colors(cub3d, line + i));
	else if (ft_strnstr(line + i, "NO", 2) || ft_strnstr(line + i, "SO", 2)
		|| ft_strnstr(line + i, "WE", 2) || ft_strnstr(line + i, "EA", 2))
		return (check_texture(cub3d, line + i, 2));
	else if (line[i] == '1' || line[i] == '0')
		return (check_map(cub3d, line, 0));
	else if (line[i] != '\n' && line[i] != '\0')
		return (5);
	else if (cub3d->map.rows > 0 && (line[i] == '\n' || line[i] == '\0'))
		cub3d->file.after_map = true;
	return (0);
}

void	check_file(t_cub3d *cub3d, char *line, int r_code)
{
	line = get_next_line(cub3d->map_fd);
	if (line == NULL)
		checkfile_error_handler(10);
	while (line != NULL)
	{
		r_code = check_line(cub3d, line, 0);
		if (cub3d->file.data_c == 6 && cub3d->map.rows == 0)
			cub3d->file.lines_till_map++;
		free(line);
		if (r_code > 0)
			clear_gnl(cub3d, r_code, 1);
		line = get_next_line(cub3d->map_fd);
	}
	free(line);
	if (cub3d->file.data_c < 6 || cub3d->map.rows == 0)
		checkfile_error_handler(6);
	else if (cub3d->map.cols < 3 || cub3d->map.rows < 3)
		checkfile_error_handler(4);
	else if (cub3d->file.player_count != 1)
		checkfile_error_handler(8);
	if (close(cub3d->map_fd) == -1)
		checkfile_error_handler(9);
	cub3d->map_fd = 0;
	cub3d->file.lines_till_map--;
}
