/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:42:27 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 13:53:03 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_type	ft_skip(char *s, int *i, int f)
{
	if (f)
	{
		while (ft_isspace(*s) && *s)
		{
			*i += 1;
			s++;
		}
		return (W_SPACE);
	}
	else
	{
		*i += ft_strchr(s + 1, *s) - s + 1;
		if (*s == '\'')
			return (S_QWORD);
		return (D_QWORD);
	}
}

void	ft_word(char *s, int *i)
{
	static char	*delm = "\'\"<>|();";

	while (s[*i])
	{
		if (!ft_strchr(delm, s[*i]) && !ft_isspace(s[*i]))
			*i += 1;
		else
			break ;
	}
}

void	hdel_offset(char *s, int *i, int *flag)
{
	static char	*delm = "<>|();";
	int			j;

	j = *i;
	while (s[*i])
	{
		if (s[*i] == '\"' || s[*i] == '\'')
			*i += ft_strchr(&s[*i] + 1, s[*i]) - &s[*i];
		if (ft_isspace(s[*i]) || ft_strchr(delm, s[*i]))
			break ;
		*i = *i + 1;
	}
	*flag = 1337;
}

t_type	parent_type(int c)
{
	if (c == '(')
		return (RPAREN);
	return (LPAREN);
}

t_type	ft_ismeta(char *str, int *i, int *flag)
{
	if (ft_strncmp(str + *i, ">>", 2) == 0)
		return (*i += 2, APPEND);
	else if (ft_strncmp(str + *i, "<<", 2) == 0)
		return (*flag = 1, *i += 2, HEREDOC);
	else if (str[*i] == '<')
		return (*i += 1, RED_IN);
	else if (str[*i] == '>')
		return (*i += 1, RED_OUT);
	else if (ft_strncmp(str + *i, "||", 2) == 0)
		return (*i += 2, OR);
	else if (ft_strncmp(str + *i, "&&", 2) == 0)
		return (*i += 2, AND);
	else if (str[*i] == '(' || str[*i] == ')')
		return (*i += 1, parent_type(str[*i]));
	else if (str[*i] == '|')
		return (*i += 1, PIPE);
	else if (str[*i] == ';')
		return (*i += 1, S_COL);
	else if (*flag && !ft_isspace(str[*i]))
		return (hdel_offset(str, i, flag), WORD);
	else if (ft_isspace(str[*i]) || str[*i] == '\"' || str[*i] == '\'')
		return (ft_skip(str + *i, i, ft_isspace(str[*i])));
	else
		return (ft_word(str, i), WORD);
}
