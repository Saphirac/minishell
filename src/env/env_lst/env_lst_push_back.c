/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:59:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:09:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief	Append a node to the end of an env list.
 * 
 * @param	list The list to append the node to.
 * @param	node The node to append to the list.
 */
void	env_lst_push_back(t_env_lst *const list, t_env *const node)
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
}
