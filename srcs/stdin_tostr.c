/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_tostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:03:20 by abahja            #+#    #+#             */
/*   Updated: 2025/04/17 13:15:45 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char *stdin_tostr(void)
{
    char *str;

    str = readline("\001\033[0;36m\002(っ◕‿◕)っ minishell $ \001\033[0m\002");
    if (!str)  
     return (NULL);
    if (!*str)
        return (NULL);
    if (ft_strcmp("exit", str) == 0)  
    {
        free(str); // the string from readline
        str = NULL;
        rl_clear_history();
        ft_malloc(0, 'f', NULL); // free every pointer i did allocate
        exit(0);
    }
    return (add_history(str), str);
}
