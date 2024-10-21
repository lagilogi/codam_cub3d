/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 18:10:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 20:01:14 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*line_fix(t_cub3d *cub3d, char *line)
{
	int		i;
	int		o;
	int		len;
	char	*fixed_line;

	i = 0;
	while (line[i] && check_whitespace(line[i]))
		i++;
	len = ft_strlen(line + i);
	fixed_line = malloc(len * sizeof(char));
	if (fixed_line == NULL)
		return (NULL);
	o = 0;
	while (o < len)
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
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_special_atoi(char *num)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	if (num[i] == '+')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
	{
		o = o * 10 + (num[i] - '0');
		if (o > 255)
			return (-1);
		i++;
	}
	if (num[i] != ',' && num[i] != '\0')
		return (-1);
	return (o);
}
