/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:16:11 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 22:29:17 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execve_fail(char *cmd)
{
	if (errno == EACCES)
	{
		perror(cmd);
		exit_status(126);
	}
	else if (errno == ENOENT)
	{
		perror(cmd);
		exit_status(127);
	}
	else if (errno == ENOEXEC)
	{
		perror(cmd);
		exit_status(1);
	}
	else
	{
		perror(cmd);
		exit_status(1);
	}
}

void	wait_child(int pid, int *status)
{
	waitpid(pid, status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(*status))
		exit_status(WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		if (exit_status(128 + WTERMSIG(*status)) == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	set_pipe(int *fds, int prev_fd)
{
	if (prev_fd != -1)
	{
		check_fail(dup2(prev_fd, STDIN_FILENO));
		check_fail(close(prev_fd));
	}
	else
		check_fail(close(fds[0]));
	if (fds[1] != -1)
	{
		check_fail(dup2(fds[1], STDOUT_FILENO));
		check_fail(close(fds[1]));
	}
}

pid_t	execute_cmd(t_eflow *flow, t_minishell *bash, int prev_fd, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		state()->is_child = 1;
		set_pipe(fds, prev_fd);
		if (!set_redirections(flow))
			final_label(exit_status(1));
		if (!flow->cmd)
			final_label(exit_status(0));
		if (flow->is_built_in)
		{
			excution_trigger(bash, flow);
			final_label(exit_status(-1));
		}
		flow->cmd = path_finder(flow, bash->env_arr);
		if (!flow->cmd)
			final_label(exit_status(-1));
		execve(flow->cmd, flow->arg, bash->env_arr);
		execve_fail(flow->cmd);
		final_label(exit_status(1));
	}
	return (pid);
}

void	pipe_cmd(t_minishell *bash)
{
	t_eflow	*flow;
	int		prev_fd;
	int		status;
	int		fd[2];
	pid_t	pid;

	flow = bash->flow;
	prev_fd = -1;
	while (flow->next)
	{
		pipe(fd);
		execute_cmd(flow, bash, prev_fd, fd);
		check_fail(close(fd[1]));
		fd[1] = -1;
		if (prev_fd != -1)
			check_fail(close(prev_fd));
		prev_fd = fd[0];
		flow = flow->next;
	}
	pid = execute_cmd(flow, bash, prev_fd, fd);
	check_fail(close(fd[0]));
	wait_child(pid, &status);
}

void	one_cmd(t_minishell *bash)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		state()->is_child = 1;
		if (!set_redirections(bash->flow))
			final_label(exit_status(1));
		if (!bash->flow->cmd)
			final_label(exit_status(0));
		bash->flow->cmd = path_finder(bash->flow, bash->env_arr);
		if (!bash->flow->cmd)
			final_label(exit_status(-1));
		execve(bash->flow->cmd, bash->flow->arg, bash->env_arr);
		execve_fail(bash->flow->cmd);
		final_label(exit_status(-1));
	}
	wait_child(pid, &status);
}
