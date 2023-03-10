/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:02:59 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:10:11 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

/**
 * @brief	Create and append a new node to the end of an env list.
 * 
 * @param	list The list to append the new node to.
 * @param	name The `name` attribute of the new node.
 * @param	value The `value` attribute of the new node. 
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	env_lst_add_back(
	t_env_lst *const list,
	char const *const name,
	char const *const value)
{
	t_env *const	node = env_new(name, value);

	if (!node)
		return (EXIT_FAILURE);
	env_lst_push_back(list, node);
	return (EXIT_SUCCESS);
}
