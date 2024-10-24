/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 16:38:26 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/11/01 15:17:58 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			return (tmp);
		else
			tmp = tmp->next;
	}
	return (tmp);
}

// int	main(void)
// {
// 	t_list	node1;
// 	t_list	node2;
// 	t_list	node3;

// 	(&node1)->content = (char *)"First original element";
// 	(&node1)->next = &node2;
// 	(&node2)->content = (char *)"Second original element";
// 	(&node2)->next = &node3;
// 	(&node3)->content = (char *)"LAST ELEMENT";
// 	(&node3)->next = NULL;
// 	printf("%p", ft_lstlast(&node1));

// 	return (0);
// }