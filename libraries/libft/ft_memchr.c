/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:27:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:54:16 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*hay;

	i = 0;
	hay = (unsigned char *) s;
	while (i < n)
	{
		if (*hay == (unsigned char) c)
			return (hay);
		else
		{
			hay++;
			i++;
		}
	}
	return (0);
}

// int main(){
// 	char s[50] = "This is a string";
// 	char c = '.';
// 	printf("%p\n", ft_memchr(s, c, 20));
// 	printf("%p", memchr(s, c, 20));

// 	return 0;
// }