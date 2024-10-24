/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:16:58 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/23 18:03:34 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

// int	main(void)
// {
// 	t_list	node1;
// 	t_list	node2;
// 	t_list	new;
// 	t_list	*head;

// 	(&node1)->content = (char *)"First original element";
// 	(&node1)->next = &node2;
// 	(&node2)->content = (char *)"Second original element";
// 	(&node2)->next = &new;
// 	(&new)->content = (char *)"LAST ELEMENT";
// 	(&new)->next = NULL;
// 	printf("%p", ft_lstadd_back(head, &new));

// 	return (0);
// }