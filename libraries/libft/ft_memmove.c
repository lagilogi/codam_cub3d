/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 13:27:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:54:00 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}

// int main(void){
// 	char dest[] = "1234!";
// 	char src[] = "There";
// 	char dest2[] = "1234!";
// 	char src2[] = "There";
// 	int x = 7;
// 	ft_memmove(dest, src, x);
// 	memmove(dest2, src2, x);
// 	printf("%s\n", dest);
// 	printf("%s", dest2);

// 	return 0;
// }