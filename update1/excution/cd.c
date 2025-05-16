/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:39:07 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 12:58:22 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	update(t_minishell *bash, char	*curr, char *old)
{
	char	*oldpwd;
	char	*currpwd;
	char	*arg[3];
	char	arg1[7];

	currpwd = ft_strjoin("PWD=", curr);
	ft_memcpy(arg1, "export", 7);
	arg[0] = arg1;
	arg[1] = currpwd;
	arg[2] = NULL;
	if (curr)
		export(arg, bash->env, bash->env_arr);
	oldpwd = ft_strjoin("OLDPWD=", old);
	arg[1] = oldpwd;
	if (old)
		export(arg, bash->env, bash->env_arr);
	ft_malloc(0, 'r', currpwd);
	ft_malloc(0, 'r', oldpwd);
	exit_status(0);
}

char	*home(char **env, char *str, int *flag)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not set\n", 2);
	*flag = 1;
	return (NULL);
}

void	cd_helper(t_minishell *bash, int *flag, char **args, char *new)
{

	if (!(*flag) && chdir(args[1]))
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(args[1], 2);
		perror(" ");
		*flag = 1;
	}
	else
	{
		new = getcwd(0, 0);
		if (new)
		{
			update(bash, new, bash->oldpwd);
			ft_malloc(0, 'r', bash->oldpwd);
			bash->oldpwd = ft_strdup(new);
			free(new);
		}
		else
		{
			ft_putstr_fd("cd: error retrieving current", 2);
			ft_putstr_fd("directory: getcwd: cannot access", 2);
			ft_putstr_fd("parent directories:	No such file or directory\n", 2);
			if (!bash->oldpwd)
				return ;
			new = ft_strdup(bash->oldpwd);
			new[ft_strrchr(new, '/') - new] = 0;
			update(bash, new, bash->oldpwd);
			bash->oldpwd = ft_strdup(new);
			ft_malloc(0, 'r', new);
		}
	}
}

void	cd(char **args, t_minishell *bash)
{
	char	*new;
	int		flag;

	new = NULL;
	if (arg_count(args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		exit_status(1);
		return ;
	}
	flag = 0;
	if (!args[1])
		args[1] = home(bash->env_arr, "HOME=", &flag);
	else if (!ft_strcmp(args[1], "-"))
		args[1] = home(bash->env_arr, "OLDPWD=", &flag);
	cd_helper(bash, &flag, args, new);
	exit_status(flag);
}
