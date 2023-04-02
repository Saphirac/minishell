/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 03:52:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 04:08:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output a syntax error message.
 * 			Also set the exit status accordingly.
 * 
 * @param	str The details to output before the error message.
 * 
 * @return	Always EXIT_ERROR.
 */
int	syntax_error(char const *const str)
{
	g_exit_code = 2U;
	if (str)
		return (ft_dprintf(STDERR_FILENO, "%s: Syntax error.\n", str),
			EXIT_ERROR);
	return (ft_dprintf(STDERR_FILENO, "Syntax error.\n"), EXIT_ERROR);
}
