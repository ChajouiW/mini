/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:41 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:13:19 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	unsigned int	i;

	if (!s)
		return (NULL);
	string = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		string[i] = f(i, s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
