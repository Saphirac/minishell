/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:33:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 18:46:51 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

/**
 * @brief	Print the given arguments to the standard output.
 * 			If an unknown option is given, it shall be considered
 * 			as an argument.
 * 
 * @details	The following options are supported:
 * 			- n: Do not output the trailing newline.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The updated exit status.
 */
int	builtin_echo(t_env_lst *const env, t_token const *const token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}
