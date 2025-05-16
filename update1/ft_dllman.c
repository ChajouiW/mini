/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:57 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:07:31 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_token	*lst_last(t_token *head)
{
	if (!head)
		return (NULL);
	while (head && head->next)
		head = head->next;
	return (head);
}

void	lst_add_back(t_token **head, t_token *new)
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

/*-------------------should handle syscalls fail-------------------------*/

void	check_fail(int returned)
{
	if (returned == -1)
	{
		ft_putstr_fd("syscall failed\n", 2);
		final_label(exit_status(1));
	}
}
