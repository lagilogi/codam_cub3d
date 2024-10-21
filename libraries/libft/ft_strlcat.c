/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 13:56:31 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/18 11:25:18 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	o;
	size_t	dstsize;

	i = 0;
	o = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i != size && dst[i])
		i++;
	dstsize = i;
	while (i < size - 1 && src[o] != '\0')
	{
		dst[i] = src[o];
		i++;
		o++;
	}
	if (i != size)
		dst[i] = '\0';
	while (src[o] != '\0')
		o++;
	return (dstsize + o);
}

// int main() {
// 	char dst[] = "asdasd";
// 	char src[] = "bbb";
// 	char dst1[] = "asdasd";
// 	char src1[] = "bbb";
// 	printf("%lu\n", ft_strlcat(dst, src, 13));
// 	printf("%lu\n\n", strlcat(dst1, src1, 13));
// 	printf("%s\n", dst);
// 	printf("%s", dst1);
// 	return 0;
// }