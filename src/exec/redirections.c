/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:41:10 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 04:11:04 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement input redirections from a file/heredoc
// TODO: implement output redirections to a file
/**
 * @brief	Apply input and output redirections,
 * 			starting with the output pipe redirection,
 * 			then any input redirection from a file/heredoc,
 * 			and finaly any output redirection to a file.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	tokens The token list containing the redirections to apply.
 * @param	fd The file descriptor to use as stdout.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	redirections(t_token_lst *const tokens, int const fd)
{
	if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (internal_error("dup2()"));
		if (close(fd))
			return (internal_error("close()"));
	}
	(void)tokens;
	return (EXIT_SUCCESS);
}
