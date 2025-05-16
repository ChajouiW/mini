/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:32:18 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 10:12:19 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	exit_status(int status)
{
	static unsigned char	exit_status;

	if (status >= 0)
		exit_status = status;
	return (exit_status);
}

void	clear_quotes(t_token *token)
{
	char	*tmp;

	tmp = token->brick;
	token->brick = ft_substr(tmp, 1, strlen(tmp) - 2);
	ft_malloc(0, 'r', tmp);
}

static int	got_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_ambiguos(t_token *t, char *s, int expanded)
{
	if (got_spaces(s) && t->type == WORD && expanded)
		t->ambiguous = 1;
}
