/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:49:58 by mochajou          #+#    #+#             */
/*   Updated: 2025/05/15 14:35:33 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	remove_space(t_token **token, t_token *t)
{
	t_token	*tmp;

	tmp = t;
	if (tmp == *token)
		*token = tmp->next;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	ft_malloc(0, 'r', tmp->brick);
	ft_malloc(0, 'r', tmp);
}

static void	join_words(t_token *t)
{
	char	*s;
	t_token	*next_one;

	next_one = t->next;
	s = t->brick;
	t->brick = ft_strjoin(t->brick, t->next->brick);
	if (next_one->ambiguous)
		t->ambiguous = next_one->ambiguous;
	t->next = t->next->next;
	if (t->next)
		t->next->prev = t;
	ft_malloc(0, 'r', s);
	ft_malloc(0, 'r', next_one->brick);
	ft_malloc(0, 'r', next_one);
}

void	ft_spacer(t_minishell *bash)
{
	t_token	*t;
	t_token	*next;

	t = bash->token;
	while (t)
	{
		if (t->type == W_SPACE)
		{
			next = t->next;
			remove_space(&bash->token, t);
			t = next;
			continue ;
		}
		if (t->next && (is_in_token_list(t->type, bash->t_word)
				&& is_in_token_list(t->next->type, bash->t_word)))
		{
			join_words(t);
			continue ;
		}
		t = t->next;
	}
}
