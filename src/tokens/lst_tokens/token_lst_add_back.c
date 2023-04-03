/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:43:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:28 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a new token with the given parameters at the end of list.
 * 		If list is empty, assign the new token to head.
 * 
 * @param list the token_lst we add to.
 * @param type type of the new node.
 * @param str str of the new node.
 * @return t_token* pointer to the new node.
 */
t_token	*token_lst_add_back(
	t_token_lst *const list,
	t_token_type const type,
	char *const str)
{
	t_token *const	node = token_new(type, str);

	if (!node)
		return (NULL);
	return (token_lst_push_back(list, node));
}
