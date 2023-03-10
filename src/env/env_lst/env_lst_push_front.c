/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:01:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:09:28 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief	Prepend a node to the beginning of an env list.
 * 
 * @param	list The list to prepend the node to.
 * @param	node The node to prepend to the list.
 */
void	env_lst_push_front(t_env_lst *const list, t_env *const node)
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
