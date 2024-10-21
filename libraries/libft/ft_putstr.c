/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 16:55:41 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/15 17:09:15 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		i++;
	return (write(1, s, i));
}
