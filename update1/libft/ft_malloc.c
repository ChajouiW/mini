/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:19 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 09:55:12 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_free(t_heapdata **heapdata)
{
	void	*ptr;

	while (*heapdata != NULL)
	{
		ptr = (*heapdata)->next;
		free((*heapdata)->ptr_h);
		free(*heapdata);
		*heapdata = (t_heapdata *)ptr;
	}
	*heapdata = NULL;
}

static t_heapdata	*ft_lstlast(t_heapdata *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static t_heapdata	*new_allocation(void *ptr, t_heapdata **ptr_heap)
{
	t_heapdata	*node;

	node = malloc(sizeof(t_heapdata));
	if (!node)
	{
		ft_free(ptr_heap);
		exit(1);
	}
	node->ptr_h = ptr;
	node->next = NULL;
	return (node);
}

static void	ft_lstadd_back(t_heapdata **lst, t_heapdata *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	new->next = NULL;
	// no need
}

void	ft_remove(t_heapdata **heap, void *p, t_heapdata *tmp)
{
	t_heapdata	*node;

	node = *heap;
	if (node->ptr_h == p)
	{
		*heap = (*heap)->next;
		free(node->ptr_h);
		node->ptr_h = NULL;
		free(node);
		node = NULL;
		return ;
	}
	while (node)
	{
		if (node->ptr_h == p)
		{
			tmp->next = node->next;
			free(p);
			node->ptr_h = NULL;
			free(node);
			return ;
		}
		tmp = node;
		node = node->next;
	}
}
/*
// void printheap(t_heapdata *heap, char flag)
// {
// 	int i = 0;
// 	printf("\n------------------------\n\n");
// 	if (flag == 'r')
// 		while (heap)
// 		{
// 			printf("%d allocated address: %p container addres
//s :%p\n", i,heap->ptr_h, heap);
// 			heap = heap->next;
// 			i++;
// 		}
// }*/

void	*collector(t_heapdata **h_d, t_heapdata **h_e, int s, char f)
{
	void	*ptr;

	if (f == 'e')
	{
		ptr = malloc(s);
		if (!ptr)
		{
			ft_free(h_e);
			final_label(1);
		}
		ft_lstadd_back(h_e, new_allocation(ptr, h_e));
		return (ptr);
	}
	ptr = malloc(s);
	if (!ptr)
	{
		ft_free(h_d);
		final_label(1);
	}
	ft_lstadd_back(h_d, new_allocation(ptr, h_d));
	return (ptr);
}

void	*ft_malloc(int size, char flag, void *to_free)
{
	static t_heapdata	*heap_data = NULL;
	static t_heapdata	*heap_env = NULL;
	void				*ptr;

	ptr = NULL;
	if (flag == 'r')
		ft_remove(&heap_data, to_free, ptr);
	else if (flag == 'f')
		ft_free(&heap_data);
	else if (flag == 'z')
		ft_free(&heap_env);
	else if (flag == 'n')
		ft_remove(&heap_env, to_free, ptr);
	else
		return (collector(&heap_data, &heap_env, size, flag));
	return (NULL);
}
