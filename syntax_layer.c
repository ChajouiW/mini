/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:36:17 by abahja            #+#    #+#             */
/*   Updated: 2025/05/01 18:29:21 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	is_in_token_list(e_type type, e_type *list)
{
	int	i = 0;
	while (list[i] != NILL)
	{
		if (list[i] == type)
			return (1);
		i++;
	}
	return (0);
}

int pipe_syntax(t_token *cur)
{
	if (!cur->prev || !cur->next || cur->next->type == PIPE)
		return (write(2, "\033[1;31mSyntax error near unexpected token `|'\033[0m\n", 51), 0);
	return 1;
}

int	redirs_syntax(t_token *token, t_minishell bash)
{
	if (!token->next || (!is_in_token_list(token->next->type, bash.t_del)
		&& !is_in_token_list(token->next->type, bash.t_word)))
		return (write(2, "\033[1;31mSyntax error near unexpected redirection \033[0m\n",54), 0);
	else if (!token->next || token->next->brick[0] == '\0') // handlit ida kan dair redirection lchi unkown value;
		return (write(2, "\033[1;31mambiguous redirect\033[0m\n",31), 0);
	return 1;
}

int syntax(t_minishell *bash)
{
	t_token  *token;
	e_type type;

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
			return (write(2, "sir tk3d hadchi mam3anach\n",27), 0);
		token = token->next;
	}
	return (1);
}

