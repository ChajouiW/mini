/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:43:44 by abahja            #+#    #+#             */
/*   Updated: 2024/11/03 08:26:45 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_same(char const *str, char c)
{
	while (*str && *str != c)
		str++;
	return (*str == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	pf;
	size_t	pe;

	if (!s1 || !set)
		return (0);
	pf = 0;
	pe = ft_strlen(s1);
	while (ft_same(set, s1[pf]))
		pf++;
	if (pf == pe)
		return (ft_strdup(""));
	while (ft_same(set, s1[pe - 1]))
		pe--;
	return (ft_substr(s1, pf, pe - pf));
}
