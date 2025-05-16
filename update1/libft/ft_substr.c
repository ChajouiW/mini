/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:16:09 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:32:25 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0)
		return (ft_strdup(""));
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len <= start + len)
		substring = (char *)ft_malloc((s_len - start + 1)
				* sizeof(char), 'x', 0);
	else
		substring = (char *)ft_malloc((len + 1) * sizeof(char), 'x', 0);
	if (!substring)
		return (NULL);
	while (s[start] && i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
