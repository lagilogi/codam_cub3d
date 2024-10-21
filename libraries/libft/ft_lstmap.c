/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 13:32:29 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/24 14:57:20 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (head == NULL)
		return (NULL);
	tmp = head;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst->content));
		if (!tmp->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (head);
}

// int	main(void)
// {
// 	t_list	n1;
// 	t_list	n2;
// 	t_list	n3;
// 	t_list	*tmp;

// 	tmp = &n1;
// 	(&n1)->content = "String 1";
// 	(&n1)->next = &n2;
// 	(&n2)->content = "2nd String";
// 	(&n2)->next = &n3;
// 	(&n3)->content = "Final";
// 	(&n3)->next = NULL;

// 	while (tmp != NULL)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
