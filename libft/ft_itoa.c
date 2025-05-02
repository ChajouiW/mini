/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:57:26 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:21:40 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(int n)
{
	size_t			i;
	long			nb;

	i = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}	
	return (i);
}

static void	ft_putnbrxd(char *result, int n)
{
	long	nbr;
	size_t	i;
	size_t	div;

	i = 0;
	div = 1;
	nbr = n;
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[i++] = '-';
		nbr = -nbr;
	}
	while (nbr / div >= 10)
		div = div * 10;
	while (div != 0)
	{
		result[i++] = (nbr / div) + '0';
		nbr = nbr % div;
		div = div / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	nblen;

	nblen = nb_len(n);
	result = (char *)malloc(sizeof(char) * nblen + 1);
	if (!result)
		return (NULL);
	ft_putnbrxd(result, n);
	result[nblen] = '\0';
	return (result);
}
