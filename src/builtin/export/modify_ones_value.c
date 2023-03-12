/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_ones_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:24:05 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 20:44:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	Modify the value of the given env node.
 * 			If an error occure during the modification,
 * 			the previous value is kept unchanged.
 * 
 * @param	node The node to modify.
 * @param	value The new value to set.
 * 
 * @return	EXIT_SUCCESS if the node was successfully modified, or
 * 			EXIT_FAILURE if an error occured.
 */
int	modify_ones_value(t_env *const node, char const *value)
{
	value = ft_strdup(value);
	if (!value)
		return (EXIT_FAILURE);
	free((void *)node->value);
	node->value = value;
	return (EXIT_SUCCESS);
}
