/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 10:44:25 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/16 14:03:13 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free2(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

int	ft_nlcheck(char	*str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin2(char *rem, char *buffer)
{
	char			*new;
	unsigned long	i;
	unsigned long	o;

	o = 0;
	if (rem == NULL)
		i = ft_strlen(buffer);
	else
		i = ft_strlen(rem) + ft_strlen(buffer);
	new = malloc(i + 1);
	if (!new)
		return (ft_free2(&rem));
	i = 0;
	while (rem != NULL && rem[i])
	{
		new[i] = rem[i];
		i++;
	}
	while (buffer[o])
		new[i++] = buffer[o++];
	new[i] = '\0';
	ft_free2 (&rem);
	return (new);
}
