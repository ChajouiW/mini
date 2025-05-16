/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:09:33 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:11:53 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	max;

	if (!lst)
		return (NULL);
	max = ft_lstsize(lst);
	while (max > 1)
	{
		lst = lst->next;
		max--;
	}
	return (lst);
}
