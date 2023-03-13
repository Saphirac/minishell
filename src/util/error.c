/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:07:21 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/13 16:07:26 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an iternal error message.
 * 
 * @param	str The details to output before the internal message error.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	internal_error(char const *const str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": internal error", STDERR_FILENO);
	return (EXIT_FAILURE);
}
