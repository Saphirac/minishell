/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_option_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:28:09 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:22:25 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an invalid option error message.
 * 
 * @param	str The details to output before the invalid option error message.
 * @param	opt The invalid option.
 * 
 * @return	Always EXIT_SUCCESS.
 */
int	invalid_option_error(char const *const str, char const *const opt)
{
	return (ft_dprintf(STDERR_FILENO, "%s: %s: invalid option\n", str, opt),
		EXIT_SUCCESS);
}
