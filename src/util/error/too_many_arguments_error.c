/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   too_many_arguments_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:28:34 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/18 02:28:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output a too many arguments error message.
 * 
 * @param	str The details to output before the too many arguments error message.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	too_many_arguments_error(char const *const str)
{
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n", str);
	return (EXIT_FAILURE);
}
