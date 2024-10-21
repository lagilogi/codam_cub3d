/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:26:24 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/11/01 15:40:14 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(int i, char **p)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}

static int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			o++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (o);
}

static int	ft_wordlength(const char *s, char c)
{
	int	o;

	o = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		o++;
	}
	return (o);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**p;

	i = 0;
	p = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (p == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			p[i] = malloc((ft_wordlength(s, c) + 1) * sizeof(char));
			if (p[i] == NULL)
			{
				ft_free(i, p);
				return (NULL);
			}
			ft_strlcpy(p[i++], s, ft_wordlength(s, c) + 1);
			s += ft_wordlength(s, c);
		}
	}
	p[i] = NULL;
	return (p);
}

// int main (){
// 	int i = 0;
// 	char str[] = " Hello World ";
// 	char del = 32:' ';

// 	int o = ft_wordcount(str, del);
// 	char **p = ft_split(str, del);
// 	while(i < o)
// 	{
// 		printf("%s\n", p[i]);
// 		i++;
// 	}
// 	return 0;
// }
