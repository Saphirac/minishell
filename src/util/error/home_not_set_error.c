/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_not_set_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:28:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/23 01:57:03 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output an error message related to the HOME environment variable
 * 			which is not set.
 * 
 * @param	str The details to output before the error message.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	home_not_set_error(char const *const str)
{
	ft_dprintf(STDERR_FILENO, "%s: HOME not set\n", str);
	return (EXIT_FAILURE);
}
