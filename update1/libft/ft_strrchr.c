/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:19:24 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:06:40 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (c == 0)
		return ((char *) s + i);
	while (&s[i--] >= &s[0])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
	}
	return (NULL);
}
