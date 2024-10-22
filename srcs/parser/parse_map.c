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

// #include "../../include/cub3d.h"

// static int set_texture(t_cub3d *cub3d, char *line, char c, char *fixed_line)
// {
// 	fixed_line = fix_line(cub3d, line);
// 	if (fixed_line == NULL)
// 		return (-1);
// 	if (c == 'N')
// 		cub3d->map.NO = mlx_load_png(fixed_line);
// 	if (cub3d->map.NO == NULL)
// 		return (-1);
// 	cub3d->map.info++;
// 	return (0);
// }

// static void	set_ground_floor(t_cub3d *cub3d, char *line, char c, int i)
// {
// 	while (line[i] && check_whitespace(line[i]))
// 		i++;
// 	if (c == 'F')
// 	{
// 		cub3d->map.f_r = ft_special_atoi(line + i);
// 		while(line[i] && line[i - 1] != ',')
// 			i++;
// 		cub3d->map.f_g = ft_special_atoi(line + i);
// 		while(line[i] && line[i - 1] != ',')
// 			i++;
// 		cub3d->map.f_b = ft_special_atoi(line + i);
// 	}
// 	else
// 	{
// 		cub3d->map.c_r = ft_special_atoi(line + i);
// 		while(line[i] && line[i - 1] != ',')
// 			i++;
// 		cub3d->map.c_g = ft_special_atoi(line + i);
// 		while(line[i] && line[i - 1] != ',')
// 			i++;
// 		cub3d->map.c_b = ft_special_atoi(line + i);
// 	}
// 	cub3d->map.info++;
// }

// static int	parse_map_info(t_cub3d *cub3d, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] && check_whitespace(line[i]))
// 		i++;
// 	if (line[i] == 'F' || line[i] == 'C')
// 	{
// 		set_ground_floor(cub3d, line + i + 1, line[i], 0);
// 		return (0);
// 	}
// 	else if (ft_strnstr(line + i, "NO", 2) || ft_strnstr(line + i, "SO", 2) || ft_strnstr(line + i, "WE", 2) || ft_strnstr(line + i, "EA", 2))
// 	{
// 		if (set_texture(cub3d, line + i + 2, line[i], NULL) == -1)
// 			return (-1);
// 		return (0);
// 	}
// 	if (line[i] == '1' || line[i] == '0')
// 		return (-1);
// 	return (0);
// }

// void	parse_map(t_cub3d *cub3d)
// {
// 	char	*line;
		
// 	line = get_next_line(cub3d->map_fd);
// 	if (line == NULL)
// 		close_program(cub3d, "empty file", 1);
// 	while (line != NULL && cub3d->map.info < 6)
// 	{
// 		if (parse_map_info(cub3d, line) == -1)
// 		{
// 			free(line);
// 			close_program(cub3d, "Error in map parsing\n", 1);
// 		}
// 		free(line);
// 		line = get_next_line(cub3d->map_fd);
// 	}
// 	if (cub3d->map.info < 6)
// 		close_program(cub3d, "Missing map information\n", 1);
// 	free(line);
// }
