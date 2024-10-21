/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 15:56:23 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/15 17:35:36 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// int main(){
//     char s[] = "tripouille";
//     size_t i = 0;
//     size_t o = 42000;
//     char *q = ft_substr(s, i, o);
//     printf("%p\n", q);
//     printf("%s", q);
//     return 0;
// }