/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_a_directory_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 03:00:04 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:28:23 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to a path
 * 			which does not refer to a directory whereas it should.
 * 
 * @param	str The details to output before the error message.
 * @param	path The path which does not refer to a directory.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	not_a_directory_error(char const *const str, char const *const path)
{
	if (str)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: Not a directory\n",
				str, path), EXIT_FAILURE);
	return (ft_dprintf(STDERR_FILENO, "%s: %s: Not a directory\n", str, path),
		EXIT_FAILURE);
}
