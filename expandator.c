/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:07:11 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/03 16:09:34 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include <string.h>

static void	clear_quotes(t_token *token)
{
	char	*tmp;

	tmp = token->brick;
	token->brick = ft_substr(tmp, 1, strlen(tmp) - 2);
	ft_malloc(0, 'r', tmp);
}

static char	*get_value2(t_env *env, char *s, char *key)
{
	char	*value;
	char	*tmp;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value + 1));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*get_value(t_env *env, char *s)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;
	static char	*del = "\'\"\\/$";

	i = -1;
	while (s[++i])
	{
		if (s[i + 1] && s[i] == '$' && !ft_isspace(s[i + 1]))
		{
			j = i + 1;
			while (s[j] && (!ft_isspace(s[j]) && !ft_strchr(del, s[j])))
				j++;
			tmp = ft_substr(s + 1 + i, 0, j - i - 1);
			value = get_value2(env, s, tmp);
			ft_malloc(0, 'r', tmp);
			tmp = ft_substr(s, 0, i);
			tmp = ft_strjoin(tmp, value);
			s = ft_strjoin(tmp, &s[j]);
			i += ft_strlen(value) - 1;
			ft_malloc(0, 'r', value);
		}
	}
	return (ft_strdup(s));
}

// static const char *token_type_to_str(e_type type)
// {
//     switch (type) {
//         case WORD:         return "WORD";
//         case PIPE:         return "PIPE";
//         case RED_IN:  return "RED_IN";
//         case RED_OUT: return "RED_OUT";
//         case APPEND:       return "APPEND";
//         case HEREDOC:      return "HEREDOC"; 
// 		case S_QWORD:      return "SINGLE_QUOTE";
// 		case D_QWORD:      return "DOUBLE_QUOTE";
// 		case W_SPACE: 	return "space";
// 		case OR:		   return "OR";
// 		case LPAREN:		return "LPAREN";
// 		case RPAREN: 		return "RPAREN";
// 		case AND:		  return "AND";
// 		case S_COL:			return "S_COL";
// 		case Q_DEL:			return "QUOTED_DEL";
// 		case DEL:  			return "DELimeter";
//         default:           return "UNKNOWN";
//     }
// }
void	expandator(t_minishell *bash, int f)
{
	t_token	*t;
	char	*tmp;

	t = bash->token;
	while (t)
	{
		if (t->type == D_QWORD || t->type == S_QWORD)
			clear_quotes(t);
		if (f && t->type != W_SPACE)
		{
			f = 0;
			t = t->next;
			continue ;
		}
		if (t->type == HEREDOC)
			f = 1;
		if (t->type != S_QWORD && ft_strchr(t->brick, '$'))
		{
			tmp = t->brick;
			t->brick = get_value(bash->env, tmp);
			ft_malloc(0, 'r', tmp);
		}
		t = t->next;
	}
	ft_spacer(bash);
}
