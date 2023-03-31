/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_del_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:12:06 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:17:45 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove one node from a pid list.
 * 
 * @param	list The list to remove the node from.
 * @param	node The node to remove.
 */
void	pid_lst_del_one(t_pid_lst *const list, t_pid *const node)
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
	free(node);
}
