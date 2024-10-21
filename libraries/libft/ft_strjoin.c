/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 10:21:57 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/11/09 17:59:14 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		o;
	char	*p;

	i = 0;
	o = ft_strlen(s1) + ft_strlen(s2);
	p = malloc((o + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (*s1)
	{
		p[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		p[i] = *s2;
		i++;
		s2++;
	}
	p[i] = '\0';
	return (p);
}

// int main(){
// 	char s1[] = "Hello ";
// 	char s2[] = "World!";
// 	char *q = ft_strjoin(s1, s2);

// 	printf("%s\n", q);
// 	printf("%p", q);

// 	return 0;
// }