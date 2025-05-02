/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:12:20 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:09:49 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*ntraverser;

	if (!lst || !f || !del)
		return (NULL);
	new_node = NULL;
	ntraverser = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&ntraverser, del);
			return (NULL);
		}
		ft_lstadd_back(&ntraverser, new_node);
		lst = lst->next;
	}
	return (ntraverser);
}
