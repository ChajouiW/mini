/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:12:10 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 12:56:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*file_name(unsigned int n)
{
	char			path[9];
	char			*file;
	char			*s;
	int				i;
	unsigned int	x;

	i = 0;
	x = n;
	ft_memcpy(path, "/tmp/tmp", 9);
	while (x)
	{
		i++;
		x /= 10;
	}
	s = (char *)ft_malloc(sizeof(char) * (i + 1), 'x', 0);
	s[i--] = '\0';
	while (n)
	{
		s[i--] = n % 10 + '0';
		n /= 10;
	}
	file = ft_strjoin(path, s);
	ft_malloc(0, 'r', s);
	return (file);
}

void	doc_error(char *type, char *del_doc)
{
	if (ft_strcmp("open", type) == 0)
	{
		ft_putstr_fd("Error open FD failed", 2);
		final_label(exit_status(1));
	}
	else if (ft_strcmp("EOF", type))
	{
		ft_putstr_fd("warning: here_doc delimited by EOF wanted:", 2);
		ft_putstr_fd(del_doc, 2);
		final_label(exit_status(0));
	}
}

static void	create_and_fill(char *del, char *file, char q, t_env *env)
{
	int		fd;
	char	*content;

	content = file;
	if (access(file, F_OK) == 0)
		unlink(file);
	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		doc_error("open", NULL);
	while (content && ft_strcmp(content, del))
	{
		content = readline("> ");
		if (!content)
			doc_error("EOF", del);
		if (ft_strcmp(content, del))
		{
			if (!q && ft_strchr(content, '$'))
				content = get_value(env, content, -1, 0);
			content = ft_strjoin(content, "\n");
			ft_putstr_fd(content, fd);
		}
	}
	check_fail(close(fd));
	final_label(exit_status(0));
}

static char	*doc_content(char *del, char q, t_env *env, int *status)
{
	static unsigned int	suffix;
	char				*file;
	int					id;

	suffix++;
	file = file_name(suffix);
	id = fork();
	if (id == -1)
		final_label(0);
	if (id != 0)
		(state())->is_heredoc = 1;
	if (id == 0)
	{
		signal(SIGINT, handle_doc);
		create_and_fill(del, file, q, env);
	}
	waitpid(id, status, 0);
	exit_status(WEXITSTATUS(*status));
	(state())->is_heredoc = 0;
	return (file);
}

int	here_doc(t_minishell *bash)
{
	t_eflow	*flow;
	t_re	*re;
	int		status;

	flow = bash->flow;
	while (flow)
	{
		re = flow->redirs;
		while (re)
		{
			if (re->type == HEREDOC)
			{
				re->filename = doc_content(re->del, re->q_del,
						bash->env, &status);
				if (exit_status(-1) != 0)
					return (1);
				re->type = RED_IN;
			}
			re = re->next;
		}
		flow = flow->next;
	}
	return (0);
}
