/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_kill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:49:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 20:50:49 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Iterate over a pid list and kill every process it contains.
 * 
 * @param	list The list to iterate over.
 * @param	sig The signal to send to the processes.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pid_lst_kill(t_pid_lst *const list, int const sig)
{
	t_pid const	*node = list->head;

	while (node)
	{
		if (kill(node->pid, sig))
			return (EXIT_FAILURE);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
