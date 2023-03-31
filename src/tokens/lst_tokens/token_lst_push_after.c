/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_push_after.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 07:03:06 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 07:06:29 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Insert a token after another one in a token list.
 * 
 * @param	list	The list to insert the node to.
 * @param	prev	The node to insert the node after.
 * @param	node	The node to insert.
 * 
 * @return	A pointer to the inserted node.
 */
t_token	*token_lst_push_after(
	t_token_lst *const list,
	t_token *const prev,
	t_token *const node)
{
	if (!prev->next)
		return (token_lst_push_back(list, node));
	node->next = prev->next;
	node->prev = prev;
	prev->next->prev = node;
	prev->next = node;
	++list->size;
	return (node);
}
