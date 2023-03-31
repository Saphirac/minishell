/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:40:40 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:48:43 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Allocate a new pid node, initialize its attributes,
 * 			and prepend it to the beginning of a pid list.
 * 
 * @param	list The list to prepend the new node to.
 * @param	pid The process id to store in the node.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pid_lst_add_front(t_pid_lst *const list, int const pid)
{
	t_pid *const	node = pid_new(pid);

	if (!node)
		return (EXIT_FAILURE);
	pid_lst_push_front(list, node);
	return (EXIT_SUCCESS);
}
