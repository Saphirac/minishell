/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_del_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:34:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:52:49 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove links from a str list to a specific node.
 * 			Links from the node to the list are preserved.
 * 
 * @details	Giving a node which is not part of the list
 * 			causes undefined behavior.
 * 
 * @param	list The list to remove the node from.
 * @param	node The node to remove.
 */
void	str_lst_del_one(t_str_lst *const list, t_str *const node)
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
	free(node->str);
	free(node);
}
