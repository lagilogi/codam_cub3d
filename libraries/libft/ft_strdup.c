/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 14:29:03 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 10:32:47 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	c;
	size_t	i;
	char	*p;

	c = ft_strlen(s);
	i = c + 1;
	p = malloc(i);
	if (p == NULL)
		return (NULL);
	while (i > 0)
	{
		*p = *s;
		s++;
		i--;
		if (i > 0)
			p++;
	}
	return (p - c);
}

// int main(){
// 	int i = 0;
// 	char s[] = "Hey";
// 	printf("%p\n", s);

// 	char *q = ft_strdup(s);
// 	printf("%p\n", q);
// 	printf("%s", q);

// 	return 0;
// }