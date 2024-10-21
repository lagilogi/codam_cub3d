/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:23:49 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 18:57:00 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_setchecker(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char		*p;
	const char	*l;

	i = 0;
	while (ft_setchecker(set, *s1) == 1 && *s1)
		s1++;
	l = s1 + ft_strlen(s1) -1;
	while (l > s1 && ft_setchecker(set, *l))
		l--;
	i = l - s1 + 1;
	p = malloc((i + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, i + 1);
	return (p);
}

// int main(){
// 	char s1[] = "osooHelloso";
// 	char set[] = "os";
// 	char* q = ft_strtrim(s1, set);
// 	printf("%s\n", q);
// 	printf("%p", q);
// 	return 0;
// }
