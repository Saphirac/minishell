/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:27:06 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/18 02:27:17 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Output a usage error message.
 * 
 * @param	prog_name The name of the program.
 * 
 * @return	Always EXIT_FAILURE.
 */
int	usage_error(char const *const prog_name)
{
	ft_dprintf(STDERR_FILENO, "Usage: %s\n", prog_name);
	return (EXIT_FAILURE);
}
