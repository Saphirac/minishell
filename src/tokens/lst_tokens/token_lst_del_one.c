/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_del_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:34:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 04:52:41 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove links from a token list to a specific node.
 * 			Links from the node to the list are preserved.
 * 
 * @details	Giving a node which is not part of the list
 * 			causes undefined behavior.
 * 
 * @param	list The list to remove the node from.
 * @param	node The node to remove.
 */
inline static void	__isolate(
	t_token_lst *const list,
	t_token const *const node)
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
}

/**
 * @brief	Remove one node from a token list, releasing its related memory.
 * 
 * @details	Giving a node which is not part of the list
 * 			causes undefined behavior.
 * 
 * @param	list The list to remove the node from.
 * @param	node The node to remove.
 * 
 * @return	The node following the removed one.
 */
t_token	*token_lst_del_one(t_token_lst *const list, t_token const *const node)
{
	t_token *const	next = node->next;

	__isolate(list, node);
	free(node->str);
	free((void *)node);
	return (next);
}
