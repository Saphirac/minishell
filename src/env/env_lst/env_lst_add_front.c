/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:32:40 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:10:21 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

/**
 * @brief	Create and prepend a new node to the beginning of an env list.
 * 
 * @param	list The list to prepend the new node to.
 * @param	name The `name` attribute of the new node. 
 * @param	value The `value` attribute of the new node. 
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	env_lst_add_front(
	t_env_lst *const list,
	char const *const name,
	char const *const value)
{
	t_env *const	node = env_new(name, value);

	if (!node)
		return (EXIT_FAILURE);
	env_lst_push_front(list, node);
	return (EXIT_SUCCESS);
}
