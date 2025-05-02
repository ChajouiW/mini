/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:19 by abahja            #+#    #+#             */
/*   Updated: 2025/04/26 16:56:53 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


static void ft_free(t_heapdata **heapdata)
{
	void *ptr;
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
static t_heapdata *new_allocation(void *ptr, t_heapdata *ptr_heap)
{
	t_heapdata *node;
	node = malloc(sizeof(t_heapdata));
	if (!node)
		ft_free(&ptr_heap);
	node->ptr_h = ptr;
	node->next = NULL;
	return node;
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
}
void	ft_remove(t_heapdata **heap, void *p)
{
	t_heapdata	*node = *heap;
	t_heapdata	*tmp;
	if (node->ptr_h == p)
	{
		*heap = (*heap)->next;
		free(node->ptr_h);
		node->ptr_h = NULL;
		free(node);
		node = NULL;
		return;
	}
	while(node)
	{
		if (node->ptr_h == p)
		{
			tmp->next = node->next;
			free(p);
			node->ptr_h = NULL;
			free(node);
			return;
		}
		tmp = node;
		node = node->next;
	}
}

void printheap(t_heapdata *heap, char flag)
{
	int i = 0;
	printf("\n------------------------\n\n");
	if (flag == 'r')
		while(heap)
		{
			printf("%d allocated address: %p container address :%p\n", i,heap->ptr_h, heap);
			heap = heap->next;
			i++;
		}
}
void *ft_malloc(int size, char flag, void *to_free)
{
	static t_heapdata *heap_data = NULL;
	
	if (flag == 'r')
		return (ft_remove(&heap_data, to_free),NULL);
	if (flag == 'f')
		return (ft_free(&heap_data), NULL);
	void *ptr;
	// flag = '\0';
	ptr = malloc(size);
	if (!ptr)
		return (ft_free(&heap_data), NULL);
	ft_lstadd_back(&heap_data,new_allocation(ptr,heap_data));
	return (ptr);
}
