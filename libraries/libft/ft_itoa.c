/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 16:10:24 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/11/07 14:08:07 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lencheck(int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len++;
		return (len);
	}
	if (n < 0)
	{
		len += 2;
		n = n / 10 * -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*p;

	i = ft_lencheck(n);
	if (n == 0)
		return (ft_strdup("0"));
	p = malloc((i + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	p[i] = '\0';
	if (n < 0)
	{
		p[--i] = n % 10 * -1 + '0';
		p[0] = '-';
		n = n / 10 * -1;
	}
	while (n > 0)
	{
		p[--i] = n % 10 + '0';
		n = n / 10;
	}
	return (p);
}

// int main(){
// 	int i = INT_MIN;
// 	printf("%s\n", ft_itoa(i));
// 	return 0;
// }
