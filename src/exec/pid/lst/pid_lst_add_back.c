/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:29:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:49:25 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Allocate a new pid node, initialize its attributes,
 * 			and append it to the end of a pid list.
 * 
 * @param	list The list to append the new node to.
 * @param	pid The process id to store in the node.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pid_lst_add_back(t_pid_lst *const list, int const pid)
{
	t_pid *const	node = pid_new(pid);

	if (!node)
		return (EXIT_FAILURE);
	pid_lst_push_back(list, node);
	return (EXIT_SUCCESS);
}
