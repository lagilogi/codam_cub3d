/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nmbrs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 16:55:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/15 17:08:57 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(long n, char *base, int count)
{
	int	i;
	int	o;

	o = 0;
	if (n >= count)
		o = ft_putnbr(n / count, base, count);
	n = n % count;
	i = base[n];
	o += write(1, &i, 1);
	return (o);
}

int	ft_nmbrs(long n, char *base)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (base[count])
		count++;
	if (n < 0)
	{
		i += ft_putchar('-');
		n = n * -1;
	}
	i += ft_putnbr(n, base, count);
	return (i);
}
