/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:27:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:27:54 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Prepend a node to the beginning of a pid list.
 * 
 * @param	list The list to prepend the node to.
 * @param	node The node to prepend to the list.
 */
void	pid_lst_push_front(t_pid_lst *const list, t_pid *const node)
{
	if (!list->size)
		list->tail = node;
	else
	{
		node->next = list->head;
		list->head->prev = node;
	}
	list->head = node;
	++list->size;
}
