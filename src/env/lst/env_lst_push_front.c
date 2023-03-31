/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:01:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 06:03:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Insert a node to the beginning of an env list.
 * 
 * @param	list The list to insert the node to.
 * @param	node The node to insert.
 * 
 * @return	A pointer to the inserted node.
 */
t_env	*env_lst_push_front(t_env_lst *const list, t_env *const node)
{
	if (!list->size)
		list->tail = node;
	else
	{
		list->head->prev = node;
		node->next = list->head;
	}
	list->head = node;
	++list->size;
	return (node);
}
