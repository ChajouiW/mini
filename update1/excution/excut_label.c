/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 08:50:11 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 21:50:00 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	is_builtin(t_eflow *target)
{
	int		i;
	char	*b_ins[8];

	b_ins[0] = "pwd";
	b_ins[1] = "cd";
	b_ins[2] = "echo";
	b_ins[3] = "export";
	b_ins[4] = "unset";
	b_ins[5] = "env";
	b_ins[6] = "exit";
	b_ins[7] = NULL;
	i = 0;
	while (b_ins[i])
	{
		if (ft_strcmp(b_ins[i], target->cmd) == 0)
		{
			target->is_built_in = 1;
			return ;
		}
		i++;
	}
}

int	count_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_setup(t_minishell *bash)
{
	char	**new_env;
	t_env	*env;
	int		size;
	int		i;

	env = bash->env;
	if (!env)
	{
		ft_putstr_fd("", 1);
		return (NULL);
	}
	size = count_size(env);
	new_env = (char **)ft_malloc(sizeof(char *) * (size + 1), 'x', NULL);
	i = 0;
	while (env)
	{
		new_env[i] = ft_strjoin(env->key, env->value);
		env = env->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	excution_trigger(t_minishell *bash, t_eflow *flows)
{
	if (ft_strcmp(flows->cmd, "export") == 0)
		export(flows->arg, bash->env, bash->env_arr);
	else if (ft_strcmp(flows->cmd, "env") == 0)
		env(bash->env_arr, bash->flow->arg);
	else if (ft_strcmp(flows->cmd, "cd") == 0)
		cd(flows->arg, bash);
	else if (ft_strcmp(flows->cmd, "pwd") == 0)
		pwd(bash);
	else if (ft_strcmp(flows->cmd, "echo") == 0)
		echo(flows->arg);
	else if (ft_strcmp(flows->cmd, "unset") == 0)
		unset(bash, flows->arg);
	else if (ft_strcmp(flows->cmd, "exit") == 0)
		exit_bash(flows->arg);
}
