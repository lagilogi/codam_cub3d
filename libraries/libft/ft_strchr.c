/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 12:58:14 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/23 14:49:46 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	x;

	x = (unsigned char) c;
	while (*s != '\0')
	{
		if (*s == x)
			return ((char *)s);
		s++;
	}
	if (*s == x)
		return ((char *)s);
	return (0);
}

// int main(){
// 	char hay[] = "tripouille";
// 	int ndl = 't' + 300;
// 	printf("%p\n", ft_strchr(hay, ndl));
// 	printf("%p\n\n", strchr(hay, ndl));
// 	printf("%s\n", ft_strchr(hay, ndl));
// 	printf("%s", strchr(hay, ndl));

// 	return 0;
// }