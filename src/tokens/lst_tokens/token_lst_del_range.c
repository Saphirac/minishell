/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_del_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:51:11 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/24 21:49:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Release every resource contained in the given token list
 * 			from the given `begin` node included
 * 			to the given `end` node excluded.
 * 			Giving any node which is not part of the list
 * 			causes undefined behavior.
 * 
 * @param	list The token list to clear.
 * @param	begin The token node to start clearing from.
 * @param	node The token node to clear the list up to.
 */
void	token_lst_del_range(
	t_token_lst *const list,
	t_token const *begin,
	t_token const *const end)
{
	t_token	*next;

	while (begin != end)
	{
		next = begin->next;
		token_lst_del_one(list, begin);
		begin = next;
	}
}
