/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_layer1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:36:23 by abahja            #+#    #+#             */
/*   Updated: 2025/05/02 22:03:27 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <unistd.h>
#include <fcntl.h>

void	ft_skinjbir(char *s, int *i)
{
	char	*delm = "\'\"<>|();";
	while(s[*i])
	{
		if (!ft_strchr(delm, s[*i]) && !ft_isspace(s[*i]))
			*i += 1;
			else
				break;
	}
}

void hdel_offset(char *s, int *i, int *flag) // heredoc increment offset;
{
	char *delm = "<>|();";
	int j;

	j = *i;
	while (s[*i])
	{
		if (s[*i] == '\"' || s[*i] == '\'')
			*i += ft_strchr(&s[*i] + 1, s[*i]) - &s[*i];
		if (ft_isspace(s[*i]) || ft_strchr(delm, s[*i]))
			break;
		*i = *i + 1;
	}
	*flag = 1337; // set the flag bach itactiva lheredoc mode flcopying;
}

e_type	ft_skip(char *s, int *i, int f)
{
	if (f)
	{
		while(ft_isspace(*s) && *s)
		{
			*i += 1;
			s++;
		}
		return (W_SPACE);
	}
	else
	{
		*i += ft_strchr(s + 1, *s) - s + 1;
		if (*s == '\'')
			return (S_QWORD);
		return (D_QWORD);
	}
}

e_type parent_type(int c)
{
	if (c == '(')
		return (RPAREN);
	return (LPAREN);
}

e_type ft_ismeta(char *str , int *i, int *flag)
{
	if (ft_strncmp(str + *i, ">>",2) == 0)
		return (*i += 2, APPEND);
	else if (ft_strncmp(str + *i, "<<",2) == 0)
		return (*flag = 1, *i += 2, HEREDOC);
	else if (str[*i] == '<')
		return (*i += 1, RED_IN);
	else if (str[*i] == '>')
		return (*i += 1, RED_OUT);
	else if (ft_strncmp(str + *i,"||", 2) == 0)
		return (*i += 2, OR);
	else if (ft_strncmp(str + *i, "&&", 2) == 0)
		return (*i += 2, AND);
	else if (str[*i] == '(' || str[*i] == ')')
		return (*i += 1 , parent_type(str[*i]));
	else if (str[*i] == '|')
		return (*i += 1,PIPE);
	else if (str[*i] == ';')
		return (*i += 1, S_COL);
	else if (*flag && !ft_isspace(str[*i]))
		return (hdel_offset(str, i, flag), WORD);
	else if (ft_isspace(str[*i]) || str[*i] == '\"' || str[*i] == '\'')
		return (ft_skip(str + *i, i, ft_isspace(str[*i])));
	else
		return (ft_skinjbir(str, i), WORD);
}

static const char *token_type_to_str(e_type type)
{
    switch (type) {
        case WORD:         return "WORD";
        case PIPE:         return "PIPE";
        case RED_IN:  return "RED_IN";
        case RED_OUT: return "RED_OUT";
        case APPEND:       return "APPEND";
        case HEREDOC:      return "HEREDOC"; 
		case S_QWORD:      return "SINGLE_QUOTE";
		case D_QWORD:      return "DOUBLE_QUOTE";
		case W_SPACE: 	return "space";
		case OR:		   return "OR";
		case LPAREN:		return "LPAREN";
		case RPAREN: 		return "RPAREN";
		case AND:		  return "AND";
		case S_COL:			return "S_COL";
		case Q_DEL:			return "QUOTED_DEL";
		case DEL:  			return "DELimeter";
        default:           return "UNKNOWN";
    }
}

void deli_type(t_token *token, char *slice, int size ,int *flag)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (slice[i] == '\'' || slice[i] == '\"')
			break;
		i++;
	}
	if (i == size)
		token->type = DEL;
	else 
		token->type = Q_DEL;
	*flag = 0; // reset flag walo as the inisial value to disable heredoc_mode
}

void heredoc_mode(t_token *new, char *slice, int size, int *flag)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	quote = 0;
	if (!new || !slice)
		return ;
	deli_type(new, slice, size, flag);
	while (i < size)
	{
		if ((slice[i] == '\'' || slice[i] == '\"') && (!quote || quote == slice[i]))
		{
			if (!quote)
				quote = slice[i];
			else
				quote = 0;
			i++;
			continue;
        }
        new->brick[j++] = slice[i++];
    }
	new->brick[j] = 0;
}

void simple_mode(t_token *new, char *slice, int size)
{
    int i = 0;

	if (!new || !slice)
 		return;
	while (i < size)
	{
		new->brick[i] = slice[i];
		i++;
	}
	new->brick[i] = '\0';
}

void ft_strnxcpy(t_token *new, char *slice, int size, int *flag)
{
	if (*flag == 1337) // heredoc mode strncpy;
		heredoc_mode(new, slice, size, flag);
	else // simple mode strncpy i know ana nadi;
		simple_mode(new,slice,size);
}
void	here_doc(t_minishell *bash);

void world_count(t_minishell *bash, int i, int j)
{
	t_token *t_new = NULL;
	e_type type;
	int flag;

	flag = 0;
	bash->token = NULL;
	i = 0;
	while (bash->prompt[i])
	{
		j = i;
		type = ft_ismeta(bash->prompt ,&i, &flag);
		t_new = create_new(i - j,type);
		ft_strnxcpy(t_new, bash->prompt + j, i - j, &flag); //idk fih
		lst_add_back(&bash->token, t_new);
	}
	expandator(bash, 0);
	if (!syntax(bash))
		return ;
	redir_recognizer(bash);
	// printf("%p\n", bash->flow->redirs);
	here_doc(bash);
	t_eflow *flow = bash->flow;
	while(flow)
	{
		while(flow->redirs)
		{
			printf("del = %s\nfile = %s\nq_del = %d\ntype = %s\n", flow->redirs->del, flow->redirs->filename, flow->redirs->q_del, token_type_to_str(flow->redirs->type));
			flow->redirs = flow->redirs->next;
		}
		flow = flow->next;
	}
}
char	*ft_itoa1(unsigned int n)
{
	unsigned int x;
	char	path[9];
	char	*file;
	int	i = 0;
	x = n;
	strcpy(path, "/tmp/tmp");
	if (!n)
		i++;
	while(x)
	{
		i++;
		x /= 10;
	}
	char	*s = (char *)ft_malloc(sizeof(char) * (i + 1), 'x', 0);
	s[i--] = '\0';
	while(n)
	{
		s[i--] = n % 10 + '0';
		n /= 10;
	}
	file = ft_strjoin(path, s);
	ft_malloc(0, 'r', s);
	return (file);
}
char	*here_content(char *del)
{
	int	id;
	int	fd;
	char	*file;
	char	*content;
	static unsigned int	file_counter;
	int	status;

	file_counter++;
	file = ft_itoa1(file_counter);
	id = fork();
	if (id == 0)
	{
		content = file;
		if (access(file, W_OK) == -1)
			unlink(file);
		fd = open(file, O_CREAT | O_RDWR);
		printf("fd = %d\n", fd);
		int len = ft_strlen(del);
		while(content && !ft_strnstr(del, content, len))
		{
			content = readline("> ");
			if (!ft_strnstr(del, content, len))
				write(fd, content, ft_strlen(content));
		}
		close(fd);
		exit(1);
	}
	waitpid(id, &status, 0);
	return (file);
}
void	here_doc(t_minishell *bash)
{
	t_eflow *flow = bash->flow;
	t_re *re;

	while(flow)
	{
		if (re)
		re = flow->redirs;
		if (!re)
			printf("hh\n");
		while(re)
		{
			if (re->type == HEREDOC)
			{
				re->filename = here_content(re->del);
				re->type = RED_IN;
			}
			re = re->next;
		}
		flow = flow->next;
	}
}