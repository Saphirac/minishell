/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 04:19:17 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 04:29:18 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Ouptut an ambiguous redirect error message.
 * 			Also set the exit status accordingly.
 * 
 * @param	str The details to output before the error message.
 * 
 * @return	Always EXIT_SUCCESS.
 */
int	ambiguous_redirect_error(char const *const str)
{
	g_exit_code = 1U;
	if (str)
		return (ft_dprintf(STDERR_FILENO, "%s: ambiguous redirect.\n"),
			EXIT_FAILURE);
	return (ft_dprintf(STDERR_FILENO, "ambiguous redirect.\n"), EXIT_SUCCESS);
}
