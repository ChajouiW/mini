/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:38:48 by abahja            #+#    #+#             */
/*   Updated: 2025/05/13 15:47:47 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern char	**environ;

t_env	*create(char *s)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), 'e', NULL);
	new->key = ft_envsubstr(s, 0, ft_strchr(s, '=') - s);
	new->value = ft_envstrdup(ft_strchr(s, '='));
	new->next = NULL;
	return (new);
}

void	add_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!head || !(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*copy_env(void)
{
	int		i;
	t_env	*env;
	t_env	*new;

	i = 0;
	env = NULL;
	new = NULL;
	while (environ[i])
	{
		new = create(environ[i]);
		add_back(&env, new);
		i++;
	}
	if (!env)
		env = create("");
	return (env);
}
