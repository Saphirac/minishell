/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:35:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 07:09:17 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_lst_add_front(
	t_token_lst *const list,
	t_token_type const type,
	char *const str)
{
	t_token *const	node = token_new(type, str);

	if (!node)
		return (NULL);
	return (token_lst_push_front(list, node));
}
