/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:53:35 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:11:11 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_envstrdup(const char *s)
{
	size_t	s_os;
	char	*dup;

	if (!s)
		return (NULL);
	s_os = ft_strlen(s) + 1;
	dup = (char *)ft_malloc(s_os * sizeof(char), 'e', 0);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, s_os);
	return (dup);
}

char	*ft_envsubstr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0)
		return (ft_envstrdup(""));
	if (start >= s_len)
		return (ft_envstrdup(""));
	if (s_len <= start + len)
		substring = (char *)ft_malloc((s_len - start + 1)
				* sizeof(char), 'e', 0);
	else
		substring = (char *)ft_malloc((len + 1) * sizeof(char), 'e', 0);
	if (!substring)
		return (NULL);
	while (s[start] && i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
