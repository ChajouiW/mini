/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:07:11 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 22:05:31 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include <string.h>

static char	*get_value2(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value + 1));
		env = env->next;
	}
	return (ft_strdup(""));
}

static void	expande(char **s, int *i, int j, t_env *env)
{
	char	*value;
	char	*tmp;
	char	*slice;
	char	*old;

	old = *s;
	slice = ft_substr(old + 1 + *i, 0, j - *i - 1);
	value = get_value2(env, slice);
	ft_malloc(0, 'r', slice);
	slice = ft_substr(old, 0, *i);
	tmp = slice;
	slice = ft_strjoin(slice, value);
	ft_malloc(0, 'r', tmp);
	*s = ft_strjoin(slice, &old[j]);
	*i += ft_strlen(value) - 1;
	ft_malloc(0, 'r', old);
	ft_malloc(0, 'r', value);
	ft_malloc(0, 'r', slice);
}

static void	expande2(int *i, char **s)
{
	char	*value;
	char	*tmp;
	char	*slice;
	char	*old;

	old = *s;
	value = ft_itoa(exit_status(-1));
	slice = ft_substr(old, 0, *i);
	tmp = ft_strjoin(slice, value);
	*s = ft_strjoin(tmp, &old[*i + 2]);
	*i += ft_strlen(value) - 1;
	ft_malloc(0, 'r', value);
	ft_malloc(0, 'r', tmp);
	ft_malloc(0, 'r', slice);
	ft_malloc(0, 'r', old);
}

char	*get_value(t_env *env, char *s, char check, t_token *t)
{
	char		*tmp;
	int			i;
	int			j;

	tmp = s;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1])
				|| s[i + 1] == '_' || !s[i + 1]))
		{
			if (!s[i + 1] && !check)
				continue ;
			j = i + 1;
			while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
				j++;
			expande(&s, &i, j, env);
		}
		else if (!ft_strncmp(&s[i], "$?", 2))
			expande2(&i, &s);
	}
	if (check != -1)
		check_ambiguos(t, s, (tmp != s));
	if (tmp != s)
		ft_malloc(0, 'r', tmp);
	return (s);
}

void	expandator(t_minishell *bash, int f)
{
	t_token	*t;

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
			t->brick = get_value(bash->env, t->brick,
					(t->next && t->next->type != W_SPACE), t);
		t = t->next;
	}
}
