/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:59:17 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:09:39 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
/*creates*/

t_token	*create_new(int size, t_type type)
{
	t_token	*new;

	new = (t_token *)ft_malloc(sizeof(t_token), 'x', NULL);
	new->brick = (char *)ft_malloc(sizeof(char) * (size + 1), 'x', NULL);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	new->visited = 0;
	new->ambiguous = 0;
	return (new);
}

void	flow_add_new(t_eflow **flow, t_eflow *nflow)
{
	t_eflow	*tmp;

	if (!flow || !nflow)
		return ;
	if (!*flow)
	{
		*flow = nflow;
		return ;
	}
	tmp = *flow;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = nflow;
	nflow->prev = tmp;
}

t_eflow	*create_flow(t_re *redirs)
{
	t_eflow	*flow;

	flow = ft_malloc(sizeof(t_eflow), 'x', 0);
	flow->cmd = NULL;
	flow->arg = NULL;
	flow->is_built_in = 0;
	flow->redirs = redirs;
	flow->next = NULL;
	flow->prev = NULL;
	return (flow);
}

void	re_add_new(t_re **redirs, t_re *nredir)
{
	t_re	*tmp;

	if (!redirs || !nredir)
		return ;
	if (!*redirs)
	{
		*redirs = nredir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = nredir;
}

t_re	*create_re(t_type type, t_token *token)
{
	t_re	*redir;

	redir = ft_malloc(sizeof(t_re), 'x', 0);
	redir->filename = NULL;
	redir->del = NULL;
	redir->q_del = 0;
	if (type == RED_IN || type == RED_OUT || type == APPEND)
		redir->filename = ft_strdup(token->brick);
	else if (type == HEREDOC)
	{
		redir->del = ft_strdup(token->brick);
		if (token->type == Q_DEL)
			redir->q_del = 1;
	}
	redir->type = type;
	redir->next = NULL;
	return (redir);
}
