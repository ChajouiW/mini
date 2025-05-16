/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:37:10 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 22:11:47 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_sig	*state(void)
{
	static t_sig	state;

	return (&state);
}

void	bash_signal(int sig)
{
	t_sig	*stat;

	stat = state();
	(void)sig;
	exit_status(128 + SIGINT);
	if (!stat->is_excution && !stat->is_heredoc)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 1);
}
