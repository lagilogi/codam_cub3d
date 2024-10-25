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

static int set_texture(t_cub3d *cub3d, char *txtr_str, char c)
{
	if (c == 'N')
	{
		cub3d->map.NO = mlx_load_png(txtr_str);
		if (cub3d->map.NO == NULL)
			return (2);
	}
	if (c == 'S')
	{
		cub3d->map.SO = mlx_load_png(txtr_str);
		if (cub3d->map.SO == NULL)
			return (2);
	}
	if (c == 'W')
	{
		cub3d->map.WE = mlx_load_png(txtr_str);
		if (cub3d->map.WE == NULL)
			return (2);
	}
	if (c == 'E')
	{
		cub3d->map.EA = mlx_load_png(txtr_str);
		if (cub3d->map.EA == NULL)
			return (2);
	}
	return (0);
}

static int	get_txtr_str(t_cub3d *cub3d, char *line)
{
	int		i;
	int		o;
	int		len;
	char	*txtr_str;

	i = 2;
	while (check_whitespace(line[i]))
		i++;
	len = ft_strlen(line + i);
	txtr_str = malloc(len * sizeof(char));
	if (txtr_str == NULL)
		return (1);
	o = 0;
	while (o < len - 1)
		txtr_str[o++] = line[i++];
	txtr_str[o] = '\0';
	if (set_texture(cub3d, txtr_str, line[0]) > 0)
	{
		free (txtr_str);
		return (2);
	}
	free (txtr_str);
	return (-1);
}

static int	parse_line(t_cub3d *cub3d, char *line, int i)
{
	int	r_code;

	while (line[i] && check_whitespace(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		return (-1);
	else if (ft_strnstr(line + i, "NO", 2) || ft_strnstr(line + i, "SO", 2) || ft_strnstr(line + i, "WE", 2) || ft_strnstr(line + i, "EA", 2))
	{
		r_code = get_txtr_str(cub3d, line + i);
		return (r_code);
	}
	return (0);
}

void	parse_file(t_cub3d *cub3d, char *input)
{
	char	*line;
	int		r_code;
	int		addit_info;

	addit_info = 0;
	cub3d->map_fd = open(input, O_RDONLY);
	if (cub3d->map_fd == -1)
		error_handler(3);
	line = get_next_line(cub3d->map_fd);
	if (line == NULL)
		parsefile_error_handler(cub3d, 1);
	while (line != NULL)
	{
		r_code = parse_line(cub3d, line, 0);
		free(line);
		if (r_code == -1)
			addit_info++;
		if (addit_info == 6)
			break ;
		if (r_code > 0)
			clear_gnl(cub3d, r_code, 2);
		line = get_next_line(cub3d->map_fd);
	}
	parse_map(cub3d);
}
