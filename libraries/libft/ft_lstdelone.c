/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 11:13:20 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/24 11:42:03 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	del(lst->content);
	free(lst);
}
