/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:17:20 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/23 11:19:57 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*next;

	if (!lst)
		return ;
	list = *lst;
	while (list != NULL)
	{
		next = list->next;
		ft_lstdelone(list, del);
		list = next;
	}
	*lst = NULL;
}
