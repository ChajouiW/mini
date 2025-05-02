/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:57 by abahja            #+#    #+#             */
/*   Updated: 2025/04/17 13:13:32 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_token *lst_last(t_token *head)
{
	if (!head)
		return NULL;
	while (head && head->next)
	{
		head = head->next;
	}
	return (head);
}
void lst_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;
	
	if (!*head || !head)
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = lst_last(*head);
		tmp->next = new;
		new->prev = tmp; 
		return ;
	}		
}