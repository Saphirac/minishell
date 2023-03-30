/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:06:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/29 17:32:41 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_lst_add_after(t_token_lst *const token_lst, t_token *const token,
		t_token_type const type, char *const str)
{
	t_token	*node;

	if (!token->next)
		return (token_lst_add_back(token_lst, type, str));
	node = token_new(type, str);
	if (!node)
		return (EXIT_FAILURE);
	token->next->prev = node;
	node->next = token->next;
	token->next = node;
	node->prev = token;
	++token_lst->size;
	return (EXIT_SUCCESS);
}
