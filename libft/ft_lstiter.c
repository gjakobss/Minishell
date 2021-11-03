/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:17:52 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/23 11:18:02 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temporary;

	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		temporary = lst->next;
		f(lst->content);
		lst = temporary;
	}
}
