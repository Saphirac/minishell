/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:35:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 16:05:25 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/**
 * @brief	Exit the shell, with either the given status code as argument,
 * 			or the last saved status code.
 * 			If the argument count is greater than 1,
 * 			the shell is not exited, and an error is output.
 * 			If the argument contains a non-numerical character,
 * 			the shell is exited, and an error is output.
 * 			If the argument value is outside of the range [0 ; 255],
 * 			the shell is exited with an undefined exit status code.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The updated exit status.
 */
int	builtin_exit(t_env_lst *const env, t_token const *token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}
