/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:19:24 by abahja            #+#    #+#             */
/*   Updated: 2024/11/02 11:21:50 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

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
