/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 13:55:19 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/23 14:45:26 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	x = (unsigned char) c;
	if (x > 127)
		return ((char *)s);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == x)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

// int main(){
// 	char hay[] = "haystacks";
// 	char ndl = 'h';
// 	printf("%p\n", strrchr(hay, ndl));
// 	printf("%p\n", ft_strrchr(hay, ndl));
// 	return 0;
// }
