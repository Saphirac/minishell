/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:36:01 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 16:05:36 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/**
 * @brief	Print the current working directory to the standard output.
 * 			Neither options nor arguments are supported.
 * 			If any are given, an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The updated exit status.
 */
int	builtin_pwd(t_env_lst *const env, t_token const *token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}
