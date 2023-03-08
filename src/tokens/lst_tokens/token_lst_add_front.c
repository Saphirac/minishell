/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:35:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 20:01:08 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_lst_add_front(t_token_lst *const list,
	int const type, char *const str)
{
	t_token *const	node = node_new(type, str);

	if (!node)
		return (EXIT_FAILURE);
	list_push_front(list, node);
	return (EXIT_SUCCESS);
}
