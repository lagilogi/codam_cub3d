/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 11:19:31 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:51:17 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		o = 0;
		while (big[i] == little[o] && i < len)
		{
			if (little[o + 1] == '\0')
				return ((char *)(big + (i - o)));
			i++;
			o++;
		}
		i = i - o;
		i++;
	}
	return (0);
}

// int main(){
// 	char hay[] = "Needle in the aaah Haystack";
// 	char ndl[] = "asdasd";
// 	int len = 30;
// 	printf("%s\n", ft_strnstr(hay, ndl, len));
// 	printf("%p\n\n", ft_strnstr(hay, ndl, len));
// 	printf("%s\n", strnstr(hay, ndl, len));
// 	printf("%p", strnstr(hay, ndl, len));

// 	return 0;
// }