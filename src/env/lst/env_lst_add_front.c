/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:32:40 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 06:31:30 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Allocate a new env node, initialize its attributes,
 * 			and insert it to the beginning of a pid list.
 * 
 * @param	list The list to insert the new node to.
 * @param	name The `name` attribute of the new node.
 * @param	value The `value` attribute of the new node.
 * 
 * @return	A pointer to the newly created and inserted node,
 * 			or NULL if an error occured.
 */
t_env	*env_lst_add_front(
	t_env_lst *const list,
	char const *const name,
	char const *const value)
{
	t_env *const	node = env_new(name, value);

	if (!node)
		return (NULL);
	return (env_lst_push_front(list, node));
}
