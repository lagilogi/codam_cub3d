/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_fc_colors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 18:43:25 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 16:44:51 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ft_special_atoi(char *num)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	if (num[i] == '\n' || num[i] == '\0')
		return (-1);
	if (num[i] == '+')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
	{
		o = o * 10 + (num[i] - '0');
		if (o > 255)
			return (-1);
		i++;
	}
	if (num[i] != ',' && num[i] != '\n' && num[i] != '\0'
		&& !check_whitespace(num[i]))
		return (-1);
	return (o);
}

int	get_floor_color(t_cub3d *cub3d, char *line, int i)
{
	while (check_whitespace(line[i]))
		i++;
	cub3d->map.f_r = ft_special_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i++] != ',')
		return (1);
	cub3d->map.f_g = ft_special_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i++] != ',')
		return (1);
	cub3d->map.f_b = ft_special_atoi(line + i);
	if (cub3d->map.f_r == -1 || cub3d->map.f_g == -1 || cub3d->map.f_b == -1)
		return (1);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (check_whitespace(line[i]))
		i++;
	if (line[i] != '\n')
		return (1);
	return (0);
}

int	get_ceiling_color(t_cub3d *cub3d, char *line, int i)
{
	while (check_whitespace(line[i]))
		i++;
	cub3d->map.c_r = ft_special_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i++] != ',')
		return (1);
	cub3d->map.c_g = ft_special_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i++] != ',')
		return (1);
	cub3d->map.c_b = ft_special_atoi(line + i);
	if (cub3d->map.c_r == -1 || cub3d->map.c_g == -1 || cub3d->map.c_b == -1)
		return (1);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (check_whitespace(line[i]))
		i++;
	if (line[i] != '\n')
		return (1);
	return (0);
}
