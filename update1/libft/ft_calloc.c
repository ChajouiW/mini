/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:47:45 by abahja            #+#    #+#             */
/*   Updated: 2024/11/03 08:23:08 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	totz;

	totz = nmemb * size;
	s = malloc(totz);
	if (!s)
		return (NULL);
	ft_bzero(s, totz);
	return (s);
}
