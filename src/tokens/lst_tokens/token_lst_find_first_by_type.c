/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_find_first_by_type.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:32:24 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/24 01:35:11 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Search for the first token node of the given token type
 * 			in the given token list.
 * 
 * @param	list	The token list to search in.
 * @param	type	The token type to search for.
 * 
 * @return	The found token node, or NULL if none has been found.
 */
t_token	*token_lst_find_first_by_type(
	t_token_lst const *const list,
	t_token_type const type)
{
	t_token const	*node = list->head;

	while (node)
	{
		if (node->type == type)
			return ((t_token *)node);
		node = node->next;
	}
	return (NULL);
}
