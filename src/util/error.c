/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:07:21 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/14 11:44:29 by jodufour         ###   ########.fr       */
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

/**
 * @brief	Output an invalid option error message.
 * 
 * @param	str The details to output before the invalid option error message.
 * @param	opt The invalid option.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	invalid_option_error(char const *const str, char const *const opt)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: invalid option\n", str, opt);
	return (EXIT_FAILURE);
}
