/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:36:17 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 14:34:37 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_in_token_list(t_type type, t_type *list)
{
	int	i;

	i = 0;
	while (list[i] != NILL)
	{
		if (list[i] == type)
			return (1);
		i++;
	}
	return (0);
}

int	pipe_syntax(t_token *cur)
{
	if (!cur->prev || !cur->next || cur->next->type == PIPE)
	{
		ft_putstr_fd("\033[1;31mSyntax error near ", 2);
		ft_putstr_fd("unexpected token `|'\033[0m\n", 2);
		return (0);
	}
	return (1);
}

int	redirs_syntax(t_token *token, t_minishell bash)
{
	if (!token->next || (!is_in_token_list(token->next->type, bash.t_del)
			&& !is_in_token_list(token->next->type, bash.t_word)))
	{
		ft_putstr_fd("\033[1;31mSyntax error", 2);
		ft_putstr_fd("near unexpected redirection \033[0m\n", 2);
		return (0);
	}
	else if (!token->next || (!token->next->brick[0]
			&& token->next->type == WORD && token->type != HEREDOC)
		|| token->next->ambiguous)
	{
		ft_putstr_fd("\033[1;31mambiguous redirect\033[0m\n", 2);
		return (0);
	}
	return (1);
}

int	syntax(t_minishell *bash)
{
	t_token	*token;
	t_type	type;

	type = NILL;
	token = bash->token;
	while (token)
	{
		type = token->type;
		if (type == PIPE)
			if (!pipe_syntax(token))
				return (0);
		if (is_in_token_list(token->type, bash->t_redirs))
			if (!redirs_syntax(token, *bash))
				return (0);
		if (is_in_token_list(token->type, bash->t_nohandle))
			return (ft_putstr_fd("sir tk3d hadchi mam3anach\n", 2), 0);
		token = token->next;
	}
	return (1);
}
