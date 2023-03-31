/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:42:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 21:09:32 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	*str_lst_push_back(t_str_lst *const list, t_str *const node)
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
	return (node);
}
