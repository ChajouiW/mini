/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_polisher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:10 by abahja            #+#    #+#             */
/*   Updated: 2025/05/02 21:51:41 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include <stdio.h>

int is_redir(t_token *token)
{
	return (token->type == RED_IN
		|| token->type == RED_OUT
		|| token->type == HEREDOC
		|| token->type == APPEND);
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
		case OR:		   return "OR";
		case LPAREN:		return "LPAREN";
		case RPAREN: 		return "RPAREN";
		case AND:		  return "AND";
		case W_SPACE:		return "space";
		case S_COL:			return "S_COL";
        default:           return "UNKNOWN";
    }
}

void flow_info(t_eflow *flow)
{
	int x = 0;
	
	while (flow)
	{
		x++;
		printf("-----------------excution nodes info- num : %d-----------\n",x);
		printf("command flow == %s\n", flow->cmd);
		for (int i = 0; flow->arg[i]; i++)
			printf("arg[%d] = %s\t", i, flow->arg[i]);
		printf("\n");
		printf("\033[0;31mRedirections!\033[0m\n");
		t_re *re = flow->redirs; 
		while (re)
		{
			e_type type = re->type;
			printf("%s-> : %s del[quoted: %d]: %s\n" , token_type_to_str(type), re->filename,(int)(re->q_del),re->del);
			re = re->next;
		}
		printf("------------------------end info--------flow------------\n" );
		flow = flow->next;
	}
}

char	**alloc_arg(t_token *t)
{
	int	i;
	char	**args;

	i = 0;
	while(t && t->type != PIPE)
	{
		if (!t->visited)
			i++;
		t = t->next;
	}
	args = ft_malloc(sizeof(char *) * (i + 1), 'x', NULL);
	args[i] = NULL;
	return (args);
}
void	check_cmd(t_eflow *flow, t_token *t)
{
	int	i;
	
	while(t && t->visited)
		t = t->next;
	flow->arg = alloc_arg(t);
	i = 0;
	while(t && t->type != PIPE)
	{
		if (!t->visited)
		{
			if (!i)
				flow->cmd = ft_strdup(t->brick);
			flow->arg[i++] = ft_strdup(t->brick);
			t->visited = 1;
		}
		t = t->next;
	}
	if (t)
		t->visited = 2;
}

t_eflow	*ft_last(t_eflow *last)
{
	while(last->next)
		last = last->next;
	return (last);
}

void redir_recognizer(t_minishell *bash)
{
	t_token *t = bash->token; //|| \| || || | |
	e_type type;
	t_re *redirections = NULL;
	
	while (t)
	{
		while (t && t->type != PIPE)
		{
			if (is_redir(t))
			{
				type = t->type;
				t = t->next;
				if (t)
				{
					t->visited = 1;
					t->prev->visited = 1;
					re_add_new(&redirections, create_re(type, t));
				}
			}
			t = t->next;
		}
		flow_add_new(&bash->flow, create_flow(redirections));
		redirections = NULL;
		check_cmd(ft_last(bash->flow), bash->token);
		if (t && t->type == PIPE)
			t = t->next;
	}
	flow_info(bash->flow);
	// ft_malloc(0, 'f', 0);
}
