/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:10:42 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/18 15:21:29 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_char(char c, int len)
{
	char	*map_chars;
	int		i;

	i = 0;
	map_chars = "NSWE01D ";
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
		cub3d->file.no++;
	else if (ft_strnstr(line, "SO", 2))
		cub3d->file.so++;
	else if (ft_strnstr(line, "WE", 2))
		cub3d->file.we++;
	else if (ft_strnstr(line, "EA", 2))
		cub3d->file.ea++;
	else if (ft_strnstr(line, "F", 1))
		cub3d->file.floor++;
	else if (ft_strnstr(line, "C", 1))
		cub3d->file.ceil++;
	if (cub3d->file.no > 1 || cub3d->file.so > 1
		|| cub3d->file.we > 1 || cub3d->file.ea > 1)
		return (3);
	if (cub3d->file.floor > 1 || cub3d->file.ceil > 1)
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
			parsefile_error_handler(cub3d, 5);
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
