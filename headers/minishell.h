/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:00:35 by abahja            #+#    #+#             */
/*   Updated: 2025/05/02 23:27:49 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef enum {
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
}	e_type;

// typedef enum {
// 	LIST,
// 	STRING,
// 	TD_ARRAY,
// 	NODE,
// }	e_heap;

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
	e_type		type;
	struct s_re	*next;
}	t_re;

typedef struct s_eflow
{
	char			*cmd;
	char			**arg;
	t_re			*redirs;
	struct s_eflow	*next;
	struct s_eflow	*prev;
}	t_eflow;

typedef struct s_token
{
	e_type			type;
	e_type			w_t;
	char			*brick;
	int				visited;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct minishell
{
	char		*prompt;
	e_type		t_word[4];
	e_type		t_del[3];
	e_type		t_redirs[5];
	e_type		t_nohandle[6];
	t_eflow		*flow;
	t_token		*token;
	t_heapdata	*heapdata;
	t_env		*env;
}	t_minishell;

char	*stdin_tostr(void);
void	world_count(t_minishell *bash, int i, int j);
void	*ft_malloc(int size, char flag, void *to_free);
void	lst_add_back(t_token **head, t_token *new);
int		syntax(t_minishell *bash);
t_token	*create_new(int size, e_type type);
void	re_add_new(t_re **redirs, t_re *nredir);
t_re	*create_re(e_type type, t_token *token);
void	flow_add_new(t_eflow **flow, t_eflow *nflow);
t_eflow	*create_flow(t_re *redirs);
void	redir_recognizer(t_minishell *bash);
void	expandator(t_minishell *bash, int f);
int		is_in_token_list(e_type type, e_type *list);
void    ft_spacer(t_minishell *bash);
char	*get_value(t_env *env, char *s);

#endif