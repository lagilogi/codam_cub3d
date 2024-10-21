/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:32:29 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/18 17:44:30 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			min;
	int			o;

	i = 0;
	min = 1;
	o = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			min = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		o = o * 10 + (nptr[i] - '0');
		i++;
	}
	return (o * min);
}

// int main(){
// 	char str[] = "5";
// 	printf("%d\n", ft_atoi(str));
// 	printf("%d", atoi(str));
// 	return 0;
// }