/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:06:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:39 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a node t_token containing given type
 * 		and str after the t_token prev given in parameters.
 * 
 * @param list token_lst to which we add the new node.
 * @param prev token to add after.
 * @param type type of the new node.
 * @param str string of the new node.
 * @return t_token* pointer to the newly added node.
 */
t_token	*token_lst_add_after(
	t_token_lst *const list,
	t_token *const prev,
	t_token_type const type,
	char *const str)
{
	t_token *const	node = token_new(type, str);

	if (!node)
		return (NULL);
	return (token_lst_push_after(list, prev, node));
}
