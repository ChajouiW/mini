/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:25:50 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:00:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	exit_bash(char **arg)
{
	int	i;

	i = 0;
	if (count_arg(arg) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status(1);
	}
	else if (arg[1])
	{
		while (arg[1][i] && ft_isdigit(arg[1][i]))
			i++;
		if (arg[1][i])
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			final_label(exit_status(2));
		}
		else
			final_label(ft_atoi(arg[1]));
	}
	else
		final_label(exit_status(-1));
}
