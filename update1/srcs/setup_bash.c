/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:03:20 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 13:34:18 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	fd_restore(int *inods)
{
	check_fail(dup2(inods[0], STDIN_FILENO));
	check_fail(dup2(inods[1], STDOUT_FILENO));
}

void	init_pwd(t_minishell *bash)
{
	t_env	*env;
	char	*tmp;

	env = bash->env;
	tmp = getcwd(0, 0);
	bash->oldpwd = ft_strdup(tmp);
	free(tmp);
	if (!bash->oldpwd)
		ft_putstr_fd("error retrieving current directory: getcwd", 2);
	update(bash, bash->oldpwd, NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			if (access(env->value + 1, F_OK) == -1)
			{
				list_removeif(&(bash->env), env->key);
				return ;
			}
		}
		env = env->next;
	}
}

void	init_bash(t_minishell *bash, int *inods)
{
	fd_restore(inods);
	bash->t_word[0] = WORD;
	bash->t_word[1] = D_QWORD;
	bash->t_word[2] = S_QWORD;
	bash->t_word[3] = NILL;
	bash->t_del[0] = DEL;
	bash->t_del[1] = Q_DEL;
	bash->t_del[2] = NILL;
	bash->t_redirs[0] = HEREDOC;
	bash->t_redirs[1] = APPEND;
	bash->t_redirs[2] = RED_IN;
	bash->t_redirs[3] = RED_OUT;
	bash->t_redirs[4] = NILL;
	bash->t_nohandle[0] = AND;
	bash->t_nohandle[1] = OR;
	bash->t_nohandle[2] = LPAREN;
	bash->t_nohandle[3] = RPAREN;
	bash->t_nohandle[4] = S_COL;
	bash->t_nohandle[5] = NILL;
	bash->env_arr = NULL;
	bash->prompt = NULL;
	bash->flow = NULL;
	bash->token = NULL;
	bash->heapdata = NULL;
}

void	fd_backup(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
	{
		ft_putstr_fd("Error during backup std_inods\n", 2);
		final_label(exit_status(1));
	}
}

char	*stdin_prompt(void)
{
	char	*str;

	str = readline("\001\033[0;36m\002(っ◕‿◕)っminishell $ \001\033[0m\002");
	if (!str)
		final_label(0);
	add_history(str);
	return (str);
}
