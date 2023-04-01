/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:29:32 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/01 21:47:56 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Apply output pipe redirection.
 * 			Sending a pipe descriptor equal to STDOUT_FILENO does nothing. 
 * 			If an error occurs, the exit status is set accordingly,
 * 			and an error message is output on stderr.
 * 
 * @param	pd The pipe descriptor corresponding to the pipe output.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
int	pipe_redirection(int const pd)
{
	if (pd == STDOUT_FILENO)
		return (EXIT_SUCCESS);
	if (dup2(pd, STDOUT_FILENO) == -1)
		return (g_exit_code = 1U, perror("dup2()"), EXIT_FAILURE);
	if (close(pd))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
