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

static int set_texture(t_cub3d *cub3d, char *line, char c)
{
	char	*fixed_line;
	fixed_line = fix_line(line);
	if (fixed_line == NULL)
		return (-1);
	if (c == 'N')
		cub3d->map.NO = mlx_load_png(fixed_line);
	if (cub3d->map.NO == NULL)
		return (-1);
	cub3d->map.info++;
	return (0);
}

static int	parse_line(t_cub3d *cub3d, char *line, int i)
{
	int	r_code;

	while (line[i] && check_whitespace(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		return (0);
	else if (ft_strnstr(line + i, "NO", 2) || ft_strnstr(line + i, "SO", 2) || ft_strnstr(line + i, "WE", 2) || ft_strnstr(line + i, "EA", 2))
	{
		r_code = set_texture(cub3d, line + i, line[i]);
		if (r_code < 0)
			return (r_code);
	}
	// else if (line[i] == '1' || line[i] == '0')
	// {
	// 	r_code = check_map(cub3d, line, 0);
	// 	if (r_code < 0)
	// 		return (r_code);
	// }
	return (0);
}

void	parse_file(t_cub3d *cub3d, char *input)
{
	char	*line;
	int		r_code;

	cub3d->map_fd = open(input, O_RDONLY);
	if (cub3d->map_fd == -1)
		error_handler(3);
	line = get_next_line(cub3d->map_fd);
	if (line == NULL)
		close_program(cub3d, "ERROR: empty file", 1);
	while (line != NULL)
	{
		r_code = parse_line(cub3d, line, 0);
		free(line);
		if (r_code > 0)
			clear_gnl(cub3d, r_code, 2);
		line = get_next_line(cub3d->map_fd);
	}
	if (close(cub3d->map_fd) == -1) 
		checkfile_error_handler(cub3d, 8);
}
