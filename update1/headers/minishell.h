/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:00:35 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 12:14:02 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>

typedef enum s_type{
	WORD,
	RED_IN,
	RED_OUT,
	APPEND,
	PIPE,
	OR,
	S_QWORD,
	D_QWORD,
	AND,
	LPAREN,
	S_COL,
	RPAREN,
	HEREDOC,
	W_SPACE,
	DEL,
	Q_DEL,
	W_CHAR,
	NILL,
}	t_type;

typedef struct sig_communication
{
	char	is_heredoc;
	char	is_excution;
	char	is_child;
}	t_sig;

typedef struct env_copy
{
	char			*key;
	char			*value;
	struct env_copy	*next;
}	t_env;

typedef struct s_heapdata
{
	void				*ptr_h;
	struct s_heapdata	*next;
}	t_heapdata;

typedef struct s_re
{
	char		*filename;
	char		*del;
	char		q_del;
	t_type		type;
	struct s_re	*next;
}	t_re;

typedef struct s_eflow
{
	char			*cmd;
	char			**arg;
	char			is_built_in;
	t_re			*redirs;
	struct s_eflow	*next;
	struct s_eflow	*prev;
}	t_eflow;

typedef struct s_token
{
	t_type			type;
	char			*brick;
	char			visited;
	char			ambiguous;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct minishell
{
	char		*oldpwd;
	char		*prompt;
	t_type		t_word[4];
	t_type		t_del[3];
	t_type		t_redirs[5];
	t_type		t_nohandle[6];
	int			std_inods[2];
	t_eflow		*flow;
	t_token		*token;
	t_heapdata	*heapdata;
	t_env		*env;
	char		**env_arr;
}	t_minishell;

void	update(t_minishell *bash, char *curr, char *old);
char	**env_setup(t_minishell *bash);
char	*stdin_prompt(void);
void	*ft_malloc(int size, char flag, void *to_free);
void	lst_add_back(t_token **head, t_token *new);
int		syntax(t_minishell *bash);
t_token	*create_new(int size, t_type type);
void	re_add_new(t_re **redirs, t_re *nredir);
t_re	*create_re(t_type type, t_token *token);
void	flow_add_new(t_eflow **flow, t_eflow *nflow);
t_eflow	*create_flow(t_re *redirs);
void	make_flow(t_minishell *bash, t_token *t, t_re *redir, t_type type);
void	expandator(t_minishell *bash, int f);
int		is_in_token_list(t_type type, t_type *list);
void	ft_spacer(t_minishell *bash);
char	*get_value(t_env *env, char *s, char check, t_token *t);
void	is_builtin(t_eflow *target);
void	exit_bash(char **arg);
void	excution_trigger(t_minishell *bash, t_eflow *flow);
char	*path_finder(t_eflow *flow, char **env);
t_type	ft_ismeta(char *str, int *i, int *flag);

/*katiexcuti lb3ab3 hhhhh salina*/
int		exit_status(int status);

void	pwd(t_minishell *bash);
void	echo(char **args);
void	env(char **env, char **arg);
void	export(char **arg, t_env *env, char **env_arr);
void	cd(char **args, t_minishell *bash);
void	unset(t_minishell *bash, char **args);
void	minishell(t_minishell *bash);
pid_t	execute_cmd(t_eflow *flow, t_minishell *bash, int prev_fd, int *fds);
int		set_redirections(t_eflow *flowblock);
void	one_cmd(t_minishell *bash);
int		add_exist(t_env *env, char *str);
char	*ft_envsubstr(char const *s, unsigned int start, size_t len);
char	*ft_envstrdup(const char *s);
char	*ft_pathjoin(char const *s1, char const *s2);
void	final_label(int exit_code);
t_sig	*state(void);
void	handle_doc(int sig);
void	check_fail(int returned);
void	clear_quotes(t_token *token);
void	check_ambiguos(t_token *t, char *s, int expanded);

void	list_removeif(t_env **env, char *key);

void	init_pwd(t_minishell *bash);
/*---------------------bash_setup---------------------------*/
void	init_bash(t_minishell *bash, int *inods);
/*made for backup fd from stdin & stdout if fails exit the caller process*/
void	fd_backup(int *stdin_backup, int *stdout_backup);
/*--set the default reactions of the ft_bash--*/
void	bash_signal(int sig);
/*-------------------env_setup-----------------------*/

/*----made for copying from environ[spesific index] \n offset to a env node--*/
t_env	*create(char *s);
/*---------append to a list of env -------*/
void	add_back(t_env **head, t_env *new);
/*-------------setup the first call env----------------*/
t_env	*copy_env(void);

/*------------------bash_core--------------------------*/
void	the_core(t_minishell *bash);
void	core_tokinizer(t_minishell *bash);
int		quotes(char *s);

/*----------------------here_doc----*/
int		here_doc(t_minishell *bash);

void	pipe_cmd(t_minishell *bash);

#endif