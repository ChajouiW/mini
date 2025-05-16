/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:37:56 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 12:58:44 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	add_exist(t_env *env, char *str)
{
	t_env	*t;
	char	*key;

	key = ft_strdup(str);
	if (ft_strchr(key, '='))
		*ft_strchr(key, '=') = 0;
	t = env;
	while (t)
	{
		if (ft_strcmp(t->key, key) == 0)
		{
			ft_malloc(0, 'n', t->value);
			t->value = ft_envstrdup(ft_strchr(str, '='));
			return (1);
		}
		t = t->next;
	}
	ft_malloc(0, 'r', key);
	return (0);
}

void	sort(char *arr[])
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				key = arr[i];
				arr[i] = arr[j];
				arr[j] = key;
			}
			j++;
		}
		i++;
	}
}

void	print_it(char **arg)
{
	int	i;

	i = 0;
	sort(arg);
	i = 0;
	while (arg[i])
		printf("declare -x %s\n", arg[i++]);
}

int	valid_key(char *key)
{
	int		i;
	char	*stop;

	stop = ft_strchr(key, '=');
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i] && &key[i] < stop)
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export(char **arg, t_env *env, char **env_arr)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (!arg[1])
		print_it(env_arr);
	while (arg[++i])
	{
		if (ft_strchr(arg[i], '=') || !*arg[i])
		{
			if (valid_key(arg[i]))
			{
				if (add_exist(env, arg[i]) != 1)
					add_back(&env, create(arg[i]));
			}
			else
			{
				ft_putstr_fd(arg[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				f = 1;
			}
		}
	}
	exit_status(f);
}
