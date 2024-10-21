/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptrs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 16:55:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/15 17:09:04 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(unsigned long long n, char *base)
{
	int	i;
	int	o;

	o = 0;
	if (n >= 16)
		o = ft_putnbr(n / 16, base);
	n = n % 16;
	i = base[n];
	o += write(1, &i, 1);
	return (o);
}

int	ft_ptrs(void *n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n == NULL)
		return (ft_putstr("(nil)"));
	else
	{
		ft_putstr("0x");
		return (ft_putnbr((unsigned long long) n, base) + 2);
	}
}
