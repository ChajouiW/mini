/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:18:59 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 11:44:38 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	long	div;

	div = 1;
	nbr = n;
	if (nbr == 0)
		ft_putchar_fd('0', fd);
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	while (nbr / div > 9)
		div = div * 10;
	while (div != 0)
	{
		ft_putchar_fd((nbr / div + '0'), fd);
		nbr = nbr % div;
		div = div / 10;
	}
}
