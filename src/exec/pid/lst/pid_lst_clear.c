/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:18:16 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:18:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove every node from a pid list,
 * 			clearing its stored data, and releasing its related memory.
 * 
 * @param	list The list to clear.
 */
void	pid_lst_clear(t_pid_lst *const list)
{
	while (list->size)
		pid_lst_del_one(list, list->head);
}
