/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:27:35 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/18 02:27:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an iternal error message.
 * 
 * @param	str The details to output before the internal error message.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	internal_error(char const *const str)
{
	ft_dprintf(STDERR_FILENO, "%s: internal error\n", str);
	return (EXIT_FAILURE);
}
