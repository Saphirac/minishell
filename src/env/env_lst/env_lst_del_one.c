/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_del_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:37:46 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 22:01:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove one node from an env list, releasing its related memory.
 * 
 * @details	Giving a node which is not part of the list
 * 			causes undefined behavior.
 * 
 * @param	list The list to remove the node from.
 * @param	node The node to remove.
 */
void	env_lst_del_one(t_env_lst *const list, t_env *const node)
{
	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else if (node == list->head)
	{
		list->head = node->next;
		list->head->prev = NULL;
	}
	else if (node == list->tail)
	{
		list->tail = node->prev;
		list->tail->next = NULL;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	--list->size;
	free((void *)node->name);
	free((void *)node->value);
	free(node);
}
