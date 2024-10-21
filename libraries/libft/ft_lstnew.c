/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 10:52:41 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/24 14:26:57 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	(*new).content = content;
	(*new).next = NULL;
	return (new);
}

// int	main(void)
// {
// 	char x = 'c';
// 	printf("%s\n", (char *)ft_lstnew(&x)->content);
// printf("%p", (char *)ft_lstnew(&x));
// 	return 0;
// }
