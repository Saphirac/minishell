/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_is_first_builtin.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 00:08:01 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/24 00:12:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Check if the first command token
 * 			of the given token list is a builtin.
 * 
 * @param	tokens The token list to check.
 * 
 * @return	true if the first command token is a builtin, or false if not.
 */
bool	token_lst_is_first_builtin(t_token_lst const *const tokens)
{
	t_token const	*node = tokens->head;

	while (node && node->type != T_COMMAND && node->type != T_BUILTIN)
		node = node->next;
	return (node && node->type == T_BUILTIN);
}
