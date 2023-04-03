/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_push_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:38:52 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Insert a token at the beggining of a list.
 * 
 * @param list The list to insert in.
 * @param node The node to insert.
 * @return t_token* pointer to the newly inserted node.
 */
t_token	*token_lst_push_front(t_token_lst *const list, t_token *const node)
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
	return (node);
}
