/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_directory_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:43:15 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:17:20 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to a file which is a directory
 * 			whereas it should not.
 * 
 * @param	str The details to output before the error message.
 * @param	path The path to the file which is actually a directory.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	is_a_directory_error(char const *const str, char const *const path)
{
	g_exit_code = 126U;
	if (str)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: Is a directory\n",
				str, path), EXIT_FAILURE);
	return (ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", path),
		EXIT_FAILURE);
}
