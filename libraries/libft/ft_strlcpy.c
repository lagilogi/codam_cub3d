/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:28:01 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/11/09 17:59:14 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// int main(){
// 	char dest[] = "";
// 	char src[] = "Byst";
// 	char dest1[] = "Hello";
// 	char src1[] = "By";
// 	printf("%lu\n", ft_strlcpy(dest, src, 6));
// 	printf("%lu\n\n", strlcpy(dest1, src1, 6));
// 	printf("%s\n", dest);
// 	printf("%s", dest1);

// 	return 0;
// }