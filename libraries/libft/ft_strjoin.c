/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:21:57 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/21 12:44:45 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		o;
	char	*p;

	i = 0;
	o = ft_strlen(s1) + ft_strlen(s2);
	p = malloc((o + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (*s1)
	{
		p[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		p[i] = *s2;
		i++;
		s2++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin_free_s2(char *s1, char *s2, char *s3)
{
	int		i;
	int		o;
	char	*p;

	i = 0;
	if (!s2)
		return (NULL);
	o = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	p = malloc((o + 1) * sizeof(char));
	if (p == 0)
		return (free(s2), NULL);
	while (*s1)
		p[i++] = *(s1++);
	o = 0;
	while (s2[o])
		p[i++] = s2[o++];
	while (*s3)
		p[i++] = *(s3++);
	p[i] = '\0';
	free(s2);
	return (p);
}

// int main(){
// 	char s1[] = "Hello ";
// 	char s2[] = "World!";
// 	char *q = ft_strjoin(s1, s2);

// 	printf("%s\n", q);
// 	printf("%p", q);

// 	return 0;
// }