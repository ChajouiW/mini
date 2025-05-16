/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:53:35 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:31:43 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_os;
	char	*dup;

	if (!s)
		return (NULL);
	s_os = ft_strlen(s) + 1;
	dup = (char *)ft_malloc(s_os * sizeof(char), 'x', 0);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, s_os);
	return (dup);
}
