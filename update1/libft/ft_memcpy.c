/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henix <henix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:22:16 by abahja            #+#    #+#             */
/*   Updated: 2024/10/27 04:14:19 by henix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destx;
	char	*srcx;

	srcx = (char *)src;
	destx = (char *)dest;
	if (!destx && !srcx)
		return (NULL);
	while (n--)
	{
		*destx = *srcx;
		destx++;
		srcx++;
	}
	return (dest);
}
