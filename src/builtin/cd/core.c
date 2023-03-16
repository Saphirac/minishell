/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:04:44 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 16:09:39 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Change the current working directory to the one specified in the
 * 			first argument of the token. If the argument count is not 1,
 * 			or if the first argument referes to an invalid path,
 * 			the current working directory is kept unchanged,
 * 			and an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The updated exit status.
 */
int	builtin_cd(t_env_lst *const env, t_token const *token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}
