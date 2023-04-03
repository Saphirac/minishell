/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:42:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:55:33 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a given node at the end of str_lst.
 * 
 * @param list str_lst we add a node to.
 * @param node the node to add.
 * @return t_str* pointer to the new node.
 */
t_str	*str_lst_push_back(t_str_lst *const list, t_str *const node)
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
