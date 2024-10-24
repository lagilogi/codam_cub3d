/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:19:06 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/18 12:47:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return ((char *)s);
}

// int main(){
// 	char str[] = "testcase";
// 	char c = 'Q';
// 	printf("%s\n\n", str);
// 	printf("%s\n", (char *)ft_memset(str, c, 3));
// 	printf("%s", (char *)memset(str, c, 3));
// }