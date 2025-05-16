/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:57:31 by abahja            #+#    #+#             */
/*   Updated: 2024/11/02 17:57:00 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	dst_len = ft_strlen(dst);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && (dst_len + i) < size - 1)
	{
		dst[dst_len + i] = src[i];
		i = i + 1;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
