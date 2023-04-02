/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_kill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:49:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 00:45:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Iterate over a pid list, kill every process it contains,
 * 			and clear it at the same time. Also set the exit status accordingly.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	list The list to iterate over.
 * @param	sig The signal to send to the processes.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pid_lst_kill(t_pid_lst *const list, int const sig)
{
	while (list->size)
	{
		if (kill(list->head->pid, sig))
			return (g_exit_code = 1U, perror("kill()"), EXIT_FAILURE);
		pid_lst_del_one(list, list->head);
	}
	return (EXIT_SUCCESS);
}
