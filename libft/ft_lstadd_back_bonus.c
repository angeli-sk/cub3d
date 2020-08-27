/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 17:56:15 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 19:13:03 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *end;

	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	end = ft_lstlast(*alst);
	end->next = new;
}
