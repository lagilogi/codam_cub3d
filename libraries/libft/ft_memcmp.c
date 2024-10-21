/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:54:06 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:54:11 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			i;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
		i++;
	}
	return (0);
}

// int main () {
// 	char string1[] = "1234567890";
// 	char string2[] = "12345a7890";
// 	int x = 10;
// 	printf("%d\n", ft_memcmp(string1, string2, x));
// 	printf("%d", memcmp(string1, string2, x));

// 	return 0;	
// }