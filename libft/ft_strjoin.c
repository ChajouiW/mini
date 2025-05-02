/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 02:18:14 by abahja            #+#    #+#             */
/*   Updated: 2025/04/27 17:42:10 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_helper(char const *s1, char const *s2, char *dest)
{
	size_t	index;

	index = 0;
	while (*s1)
		dest[index++] = *s1++;
	while (*s2)
		dest[index++] = *s2++;
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sizen;
	char	*res;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		if (s2)
			return (ft_strdup(s2));
		else
			return (ft_strdup(""));
	}
	sizen = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)ft_malloc(sizeof(char) * sizen + 1, 'x', 0);
	if (!res)
		return (res);
	res = ft_helper(s1, s2, res);
	return (res);
}
