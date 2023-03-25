/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_such_file_or_directory_error.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:31:38 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/18 02:36:41 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to an unexisting file or directory.
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
	ft_dprintf(STDERR_FILENO, "%s: %s: No such file or directory\n", str, path);
	return (EXIT_FAILURE);
}
