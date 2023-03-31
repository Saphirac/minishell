/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_not_found_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:13:29 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 06:47:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to a command
 * 			which has not been found.
 * 
 * @param	cmd The name of the command which has not been found.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	command_not_found_error(char const *const cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	return (EXIT_FAILURE);
}
