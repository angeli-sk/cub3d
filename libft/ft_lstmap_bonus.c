/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:17:28 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 18:17:31 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *temp;

	if (lst != 0)
	{
		new = ft_lstnew(f(lst->content));
		lst = lst->next;
		while (lst)
		{
			temp = ft_lstnew(f(lst->content));
			if (temp == 0)
			{
				ft_lstclear(&lst, del);
				return (0);
			}
			ft_lstadd_back(&new, temp);
			lst = lst->next;
		}
		return (new);
	}
	else
		return (0);
}
