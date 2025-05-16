/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 08:59:53 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 13:06:54 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	final_label(int exit_code)
{
	rl_clear_history();
	ft_malloc(0, 'f', 0);
	ft_malloc(0, 'z', 0);
	exit(exit_code);
}

void	handle_doc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	final_label(exit_status(128 + SIGINT));
}

int	main(void)
{
	t_minishell	bash;
	int			main_fd[2];

	fd_backup(&main_fd[0], &main_fd[1]);
	signal(SIGINT, bash_signal);
	signal(SIGQUIT, SIG_IGN);
	bash.env = copy_env();
	init_pwd(&bash);
	while (1)
	{
		init_bash(&bash, main_fd);
		bash.prompt = stdin_prompt();
		if (!bash.prompt)
			continue ;
		if (quotes(bash.prompt))
			the_core(&bash);
		else
			exit_status(1);
	}
}
