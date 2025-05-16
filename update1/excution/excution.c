/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:36:57 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 21:43:47 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && (errno == ENOENT || errno == EACCES))
	{
		perror(filename);
		return (0);
	}
	check_fail(dup2(fd, STDIN_FILENO));
	check_fail(close(fd));
	return (1);
}

int	redir_out(char *filename, char is_append)
{
	int	fd;

	if (is_append)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (errno == EACCES)
	{
		perror(filename);
		return (0);
	}
	check_fail(dup2(fd, STDOUT_FILENO));
	check_fail(close(fd));
	return (1);
}
// to check ==> in case of red_in : if exist and permission if not 
//stop redirections and exit in child
// same for red_out check just for permission

int	set_redirections(t_eflow *flow)
{
	t_re	*flowblock;

	flowblock = flow->redirs;
	while (flowblock)
	{
		if (flowblock->type == RED_IN)
		{
			if (!redir_in(flowblock->filename))
				return (0);
		}
		else if (flowblock->type == RED_OUT || flowblock->type == APPEND)
		{
			if (!redir_out(flowblock->filename, (flowblock->type == APPEND)))
				return (0);
		}
		flowblock = flowblock->next;
	}
	return (1);
}

void	minishell(t_minishell *bash)
{
	bash->env_arr = env_setup(bash);
	state()->is_excution = 1;
	if (!bash->flow->next && bash->flow->is_built_in)
	{
		if (!set_redirections(bash->flow))
			exit_status(1);
		else
			excution_trigger(bash, bash->flow);
		return ;
	}
	else if (bash->flow->next)
		pipe_cmd(bash);
	else
		one_cmd(bash);
}
