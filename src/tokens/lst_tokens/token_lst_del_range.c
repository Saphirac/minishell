/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_del_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:51:11 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 01:44:01 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove a range of nodes from a token list,
 * 			releasing their related memory.
 * 
 * @details	Giving a node which is not part of the list or
 * 			giving a `begin` node which is not before the `end` node
 * 			causes undefined behavior.
 * 
 * @param	list The list to remove the range from.
 * @param	begin The first node of the range to remove.
 * @param	end The post-last node of the range to remove.
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
