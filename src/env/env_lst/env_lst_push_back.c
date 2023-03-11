/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:59:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 02:29:55 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
