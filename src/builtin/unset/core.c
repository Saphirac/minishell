/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:36:19 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 07:10:35 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/**
 * @brief	Remove environment variables.
 * 			No options are supported.
 * 			If any are given, current environment variables are kept unchanged,
 * 			and an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The updated exit status.
 */
int	builtin_unset(t_env_lst *const env, t_token const *const token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}
