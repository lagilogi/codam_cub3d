// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   parse_utils.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/10/21 18:10:42 by wsonepou      #+#    #+#                 */
// /*   Updated: 2024/10/21 20:01:14 by wsonepou      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_char(char c, int len)
{
	char	*map_chars;
	int		i;

	i = 0;
	map_chars = "NSWE01 ";
	while (i < len)
	{
		if (map_chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_whitespace(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\v')
		return (1);
	else if (c == '\f')
		return (1);
	else if (c == '\r')
		return (1);
	return (0);
}

int	check_identifier(t_cub3d *cub3d, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		cub3d->file.NO++;
	else if (ft_strnstr(line, "SO", 2))
		cub3d->file.SO++;
	else if (ft_strnstr(line, "WE", 2))
		cub3d->file.WE++;
	else if (ft_strnstr(line, "EA", 2))
		cub3d->file.EA++;	
	else if (ft_strnstr(line, "F", 1))
		cub3d->file.F++;
	else if (ft_strnstr(line, "C", 1))
		cub3d->file.C++;
	if (cub3d->file.NO > 1 || cub3d->file.SO > 1 || cub3d->file.WE > 1 || cub3d->file.EA > 1)
		return (3);
	if (cub3d->file.F > 1 || cub3d->file.C > 1)
		return (3);
	return (0);
}

void	gnl_till_map(t_cub3d *cub3d)
{
	char	*line;
	int		i;

	i = 0;
	while (i < cub3d->file.lines_till_map)
	{
		line = get_next_line(cub3d->map_fd);
		if (line == NULL)
			parsefile_error_handler(cub3d, 1);
		free (line);
		i++;
	}
}

void	clear_gnl(t_cub3d *cub3d, int r_code, int error_h)
{
	char	*line;

	line = get_next_line(cub3d->map_fd);
	while (line != NULL)
	{
		free (line);
		line = get_next_line(cub3d->map_fd);
	}
	if (error_h == 0)
		return ;
	else if (error_h == 1)
		checkfile_error_handler(r_code);
	else if (error_h == 2)
		parsefile_error_handler(cub3d, r_code);
}
