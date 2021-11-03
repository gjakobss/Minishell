/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:43:41 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/23 13:44:14 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_cont;

	new_list = 0;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_cont = ft_lstnew(f(lst->content));
		if (!new_cont)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_list, del);
			break ;
		}
		ft_lstadd_back(&new_list, new_cont);
		lst = lst->next;
	}
	return (new_list);
}
