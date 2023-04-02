/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_such_file_or_directory_error.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:31:38 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:35:36 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to an unexisting file or directory.
 * 			Also set the exit status accordingly.
 * 
 * @param	str The details to output before the error message.
 * @param	path The path to the unexisting file or directory.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	no_such_file_or_directory_error(
	char const *const str,
	char const *const path)
{
	g_exit_code = 127U;
	if (str)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: No such file or directory\n",
				str, path), EXIT_FAILURE);
	return (ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", path),
		EXIT_FAILURE);
}
