/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 08:59:53 by abahja            #+#    #+#             */
/*   Updated: 2025/04/30 08:00:34 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"


extern char **environ;

int	quotes(char *s)
{
	while(*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			if (!ft_strchr(s + 1, *s))
				return 0;
			else
				s = ft_strchr(s + 1, *s);
		}
		s++;
	}
	return 1;
}
static t_env   *create(char *s)
{
    t_env   *new;

    new = ft_malloc(sizeof(t_env), 'x', NULL);
    new->key = ft_substr(s, 0, ft_strchr(s, '=') - s);
    new->value = ft_strdup(ft_strchr(s, '='));
    new->next = NULL;
    return new;
}
static void    add_back(t_env **head, t_env *new)
{
    t_env	*tmp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
    tmp = *head;
	while(tmp->next)
        tmp = tmp->next;
	tmp->next = new;
}
static t_env   *copy_env()
{
    int i = 0;
    t_env   *env;
    t_env   *new;

    env = NULL;
    new = NULL;
    while(environ[i])
    {
        new = create(environ[i]);
        add_back(&env, new);
        i++;
    }
    return env;
}

t_minishell init_bash(void)
{
	t_minishell bash;

	bash.t_word[0] = WORD;
	bash.t_word[1] = D_QWORD;
	bash.t_word[2] = S_QWORD;
	bash.t_word[3] = NILL;
	bash.t_del[0] = DEL;
	bash.t_del[1] = Q_DEL;
	bash.t_del[2] = NILL;
	bash.t_redirs[0] = HEREDOC;
	bash.t_redirs[1] = APPEND;
	bash.t_redirs[2] = RED_IN;
	bash.t_redirs[3] = RED_OUT;
	bash.t_redirs[4] = NILL;
	bash.t_nohandle[0] = AND;
	bash.t_nohandle[1] = OR;
	bash.t_nohandle[2] = LPAREN;
	bash.t_nohandle[3] = RPAREN;
	bash.t_nohandle[4] = S_COL;
	bash.t_nohandle[5] = NILL;
	bash.prompt = NULL;
	bash.flow = NULL;
	bash.token = NULL;
	bash.heapdata = NULL;
	return (bash);
}

 int main ()
{
	t_minishell bash;

	while (1)
	{
		bash = init_bash();
		bash.env = copy_env();
		bash.prompt = stdin_tostr();
		if (!bash.prompt)
			continue;
		if (quotes(bash.prompt))
			world_count(&bash, 0, 0);
		else 
			printf("sdha 3ad ji dwi m3aya \n");
	}
}

// int main ()
// {
// 	t_minishell bash = init_bash();
// 	 char *str = "<< \"zob\"ab";
// 	 bash.prompt = str;
// 	 bash.env = NULL;
// 		while (1)
// 		{
// 			//bash.prompt = stdin_tostr();
// 			if (!bash.prompt)
// 				continue;
// 			if (quotes(bash.prompt))
// 				world_count(&bash);
// 			else 
// 				printf("sdha 3ad ji dwi m3aya \n");
// 			break;
// 		}
// 		//free(prompt);

// }