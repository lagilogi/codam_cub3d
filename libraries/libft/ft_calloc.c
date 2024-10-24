/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 14:25:07 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/19 13:50:35 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	memsize;
	void	*p;

	if ((nmemb >= 4294967295 && size > 0) || (size >= 4294967295 && nmemb > 0))
		return (NULL);
	if (nmemb * size > 4294967295)
		return (NULL);
	memsize = nmemb * size;
	p = malloc(memsize);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, memsize);
	return (p);
}

// int main(){
// 	size_t nmemb = 2;
// 	size_t size = 3;
// 	ft_calloc(nmemb, size);
// 	return 0;
// }