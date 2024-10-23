// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   parse_map.c                                        :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/10/21 13:26:13 by wsonepou      #+#    #+#                 */
// /*   Updated: 2024/10/21 20:01:42 by wsonepou      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../include/cub3d.h"


// CHECK OOK of er lege regels in de map staan. Dat mag niet (denk ik)
static void	check_map(t_cub3d *cub3d, char *line, int i)
{
	int map_size;

	map_size = 0;
	if (cub3d->file->addit_data_count != 6)
		return (-3);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && !check_whitespace(line[i]))
			return (-4);
		else if ((line[i] == 10 || line[i] == 11 || line[i] == 12 || line[i] == 13) && line[i + 1] != '\0')
			return (-4);
		if (line[i] == '\t')
			map_size += 8 - i % 8;
		else
			map_size++;
		i++;
	}
	if (cub3d->file.map_cols < map_size)
		cub3d->file.map_cols = map_size;
	cub3d->file.map_rows++;
	return (0);
}

static void check_texture(t_cub3d *cub3d, char *line, int i)
{
	int	o;

	o = 0;
	while (line[i] && check_whitespace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (-2);
	while (line[i] != '\n' && line[i] != '\0')
	{
		i++;
		o++;
	}
	if (input[i - 4] != '.' || input[i - 3] != 'p' || input[i - 2] != 'n' || input[i - 1] != 'g')
		return (-2);
	else if (o <= 4)
		return (-2);
	cub3d->file.addit_data_count++;
	return (0);
}

static int	check_colors(t_cub3d *cub3d, char *line, int i)
{
	if (!check_whitespace(line[i]))
		return (-1);
	while (line[i] && check_whitespace(line[i]))
		i++;
	if (line[i] != '\n' || line[i] == '\0')
		return (-1);
	while (line[i] <= '0' && line[i] >= '9')
		i++;
	if (line[i] != ',')
		return (-1);
	i++;
	while (line[i] <= '0' && line[i] >= '9')
		i++;
	if (line[i] != ',')
		return (-1);
	i++;
	while (line[i] <= '0' && line[i] >= '9')
		i++;
	if (check_whitespace(line[i]))
		while (check_whitespace(line[i]))
			i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (-1);
	cub3d->file.addit_data_count++;
	return (0);
}

static void	check_line(t_cub3d *cub3d, char *line, int i)
{
	while (line[i] && check_whitespace(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		if (check_colors(cub3d, line + i + 1, 0) == -1)
			return (-1);
	else if (ft_strnstr(line + i, "NO", 2) || ft_strnstr(line + i, "SO", 2) || ft_strnstr(line + i, "WE", 2) || ft_strnstr(line + i, "EA", 2))
		if (check_texture(cub3d, line + i + 2, line[i]) == -2)
			return (-2);
	else if (line[i] == '1' || line[i] == '0')
		if (check_map(cub3d, line, 0) == -3)
			return (-3);
	else if (line[i] != '\n' && line[i] != '\0')
		return (-4);
	return (0);
}

void	check_file(t_cub3d *cub3d)
{
	char	*line;
	int		r_code;
		
	line = get_next_line(cub3d->map_fd);
	if (line == NULL)
		close_program(cub3d, "empty file", 1);
	while (line != NULL && cub3d->map.info < 6)
	{
		r_code = check_line(cub3d, line, 0);
		if (r_code < 0)
		{
			free(line);
			close_program(cub3d, "Error in map parsing\n", 1); // replace by check_file_error_handler()
		}
		cub3d->file.line_count++;
		free(line);
		line = get_next_line(cub3d->map_fd);
	}
	free(line);
	if (cub3d->map.info < 6)
		close_program(cub3d, "Missing map information\n", 1); // replace by check_file_error_handler()
	else if (cub3d->file.map_cols < 3 || cub3d->file.map_rows < 3)
		close_program(cub3d, "Invalid map size\n", 1); // replace by check_file_error_handler()
	if (close(cub3d->map_fd) == -1) 
		close_program(cub3d, "couldn't close map_fd\n", errno); // replace by check_file_error_handler()
	cub3d->map_fd = -1;
}
