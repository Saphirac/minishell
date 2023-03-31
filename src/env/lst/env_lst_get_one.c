/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_get_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:07:13 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 07:11:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Search for the node matching the given name in the given list.
 * 
 * @param	list The linked list to search in.
 * @param	name The `name` attribute of the node to search for.
 * 
 * @return	The node if found, or NULL if not.
 */
t_env	*env_lst_get_one(t_env_lst const *const list, char const *const name)
{
	t_env	*node;

	node = list->head;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}
