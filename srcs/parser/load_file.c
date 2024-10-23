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



void	load_file(t_cub3d *cub3d, char *input)
{
	char	*line;

	cub3d->map_fd = open(input, O_RDONLY);
	if (cub3d->map_fd == -1)
		error_handler(3);			// replace by load_file_error_handler()
	line = get_next_line(cub3d->map_fd);
	if (line == NULL)
		close_program(cub3d, "empty file", 1);
	while (line != NULL && cub3d->map.info < 6)
	{
		r_code = check_line(cub3d, line, 0);
		if (r_code < 0)
		{
			free(line);
			close_program(cub3d, "Error in map parsing\n", 1);
		}
		cub3d->file.line_count++;
		free(line);
		line = get_next_line(cub3d->map_fd);
	}
	if (cub3d->map.info < 6)
		close_program(cub3d, "Missing map information\n", 1);
	else if (cub3d->file.map_cols < 3 || cub3d->file.map_rows < 3)
	free(line);
}
