/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:37 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:10:55 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tempi;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tempi = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tempi;
	}
	*lst = NULL;
}
