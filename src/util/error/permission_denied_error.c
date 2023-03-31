/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:39 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 22:53:37 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output a permission denied error message.
 * 
 * @param	str The details to output before the permission denied error message.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	permission_denied_error(char const *const str)
{
	ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", str);
	return (EXIT_FAILURE);
}
