/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_del_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:37:46 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 02:29:45 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove one node from an env list,
 * 			clearing its stored data, and releasing its related memory.
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
	free(node->name);
	free(node->value);
	free(node);
}
