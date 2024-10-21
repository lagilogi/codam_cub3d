/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 13:25:36 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:54:05 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((char *) dest);
}

// Function needs to seg vault on only DEST parameter being NULL

// int main(void){
// 	char dest[] = "1234!";
// 	char src[] = "There";
// 	char dest2[] = "1234!";
// 	char src2[] = "There";
// 	ft_memcpy(dest, src, 6);
// 	memcpy(dest2, src2, 6);
// 	printf("%s\n", dest);
// 	printf("%s", dest2);
// 	return 0;
// }