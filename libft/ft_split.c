/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 04:34:01 by abahja            #+#    #+#             */
/*   Updated: 2024/11/03 08:30:50 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cw(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

static void	ft_freax(char **s, size_t cw)
{
	size_t	i;

	i = 0;
	while (i < cw)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static void	ft_mc(char **card, char const *s, char sep, size_t cw)
{
	size_t	i;
	size_t	j;
	size_t	c_index;

	i = 0;
	c_index = 0;
	while (s[i])
	{
		if (s[i] == sep && ++i)
		{
			continue ;
		}
		j = i;
		while (s[i] && s[i] != sep)
			i++;
		card[c_index] = ft_substr(s, j, (i - j));
		if (card[c_index] == NULL && c_index < cw)
		{
			ft_freax(card, c_index);
			break ;
		}
		c_index++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	cw;

	if (!s)
		return (NULL);
	cw = ft_cw(s, c);
	ret = malloc(sizeof(char *) * (cw + 1));
	if (!ret)
		return (0);
	ft_mc(ret, s, c, cw);
	ret[cw] = 0;
	return (ret);
}
