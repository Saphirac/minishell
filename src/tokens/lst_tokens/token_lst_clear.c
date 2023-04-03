/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:32:11 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:45:52 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Clear each node of the list with token_lst_del_one.
 * 
 * @param list the list to clean.
 */
void	token_lst_clear(t_token_lst *const list)
{
	while (list->size)
		token_lst_del_one(list, list->head);
}
