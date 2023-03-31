/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:23:46 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 06:38:26 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Insert a node to the end of a pid list.
 * 
 * @param	list The list to insert the node to.
 * @param	node The node to insert.
 * 
 * @return	A pointer to the inserted node.
 */
t_pid	*pid_lst_push_back(t_pid_lst *const list, t_pid *const node)
{
	if (!list->size)
		list->head = node;
	else
	{
		list->tail->next = node;
		node->prev = list->tail;
	}
	list->tail = node;
	++list->size;
	return (node);
}
