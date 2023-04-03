/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:42:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:53 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Insert a token at the end of a list.
 * 
 * @param list The list to insert in.
 * @param node The node to insert.
 * @return t_token* pointer to the newly inserted node.
 */
t_token	*token_lst_push_back(t_token_lst *const list, t_token *const node)
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
