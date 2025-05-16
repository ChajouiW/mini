/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:59:24 by abahja            #+#    #+#             */
/*   Updated: 2025/05/15 22:00:18 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	args_to_print(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
		if (arg[i])
			printf(" ");
	}
}

void	echo(char **args)
{
	int		i;
	int		j;
	char	new_line;

	i = 0;
	new_line = 1;
	while (args[++i])
	{
		j = 1;
		if ((args[i][0] == '-' && args[i][j]) && args[i][j] == 'n')
		{
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (!args[i][j])
			{
				new_line = 0;
				continue ;
			}
		}
		break ;
	}
	args_to_print(args + i);
	if (new_line)
		printf("\n");
	exit_status(0);
}
