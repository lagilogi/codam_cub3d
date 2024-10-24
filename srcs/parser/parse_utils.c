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

char	*fix_line(char *line)
{
	int		i;
	int		o;
	int		len;
	char	*fixed_line;

	i = 2;
	while (check_whitespace(line[i]))
		i++;
	len = ft_strlen(line + i);
	fixed_line = malloc(len * sizeof(char));
	if (fixed_line == NULL)
		return (NULL);
	o = 0;
	while (o < len - 1)
	{
		fixed_line[o] = line[i];
		i++;
		o++;
	}
	fixed_line[o] = '\0';
	return (fixed_line);
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

void	clear_gnl(t_cub3d *cub3d, int r_code, int error_h)
{
	char	*line;

	line = get_next_line(cub3d->map_fd);
	while (line != NULL)
	{
		free (line);
		line = get_next_line(cub3d->map_fd);
	}
	if (error_h == 1)
		checkfile_error_handler(cub3d, r_code);
	else if (error_h == 2)
		parsefile_error_handler(cub3d, r_code);
}
