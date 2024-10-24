/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 18:10:06 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 11:35:09 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main(){
// 	char s1[] = "abc";
// 	char s2[] = "abc";
// 	int x = 7;
// 	printf("%d\n", ft_strncmp(s1, s2, x));
// 	printf("%d", strncmp(s1, s2, x));

// 	return 0;
// }