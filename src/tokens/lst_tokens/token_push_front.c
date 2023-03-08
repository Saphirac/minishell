/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_push_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:38:52 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 19:56:06 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_lst_push_back(t_token_lst *const list, t_token *const node)
{
	if (!list->size)
		list->head = node;
	else
	{
		list->tail->next = node;
		node->prev = list->tail;
	}
	list->tail = node;
	++list->size;
}
