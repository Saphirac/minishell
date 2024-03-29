/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:39 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:18:00 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output a permission denied error message.
 * 			Also set the exit status accordingly.
 * 
 * @param	str The details to output before the permission denied error message.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	permission_denied_error(char const *const str)
{
	g_exit_code = 126U;
	return (ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", str),
		EXIT_FAILURE);
}
