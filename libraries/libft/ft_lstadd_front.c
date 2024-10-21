/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 13:02:35 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/23 15:33:21 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		(*new).next = *lst;
		*lst = new;
	}
}

// int	main(void)
// {
// 	t_list	lst1;
// 	t_list	lst2;
// 	t_list	*lst1_ptr;
// 	t_list	new;

// 	(&lst1)->content = (char *)"First original element";
// 	(&lst1)->next = &lst2;
// 	(&lst2)->content = (char *)"Second original element";
// 	(&lst2)->next = NULL;
// 	(&new)->content = (char *)"NEW ELEMENT";
// 	(&new)->next = NULL;
// 	lst1_ptr = &lst1;
// 	printf("%s\n", (char *)(&lst1)->content);
// 	ft_lstadd_front(&lst1_ptr, &new);
// 	printf("%s\n", (char *)lst1_ptr->content);
// }