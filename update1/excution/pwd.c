/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:35:02 by abahja            #+#    #+#             */
/*   Updated: 2025/05/16 10:11:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	pwd(t_minishell *bash)
{
	if (!bash->oldpwd)
	{
		perror("");
		exit_status(1);
	}
	else
	{
		printf("%s\n", bash->oldpwd);
		exit_status(0);
	}
}
