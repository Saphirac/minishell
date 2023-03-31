/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:29:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 06:37:30 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Allocate a new pid node, initialize its attributes,
 * 			and insert it to the end of a pid list.
 * 
 * @param	list The list to insert the new node to.
 * @param	pid The process id to store in the node.
 * 
 * @return	A pointer to the newly created and inserted node,
 * 			or NULL if an error occured.
 */
t_pid	*pid_lst_add_back(t_pid_lst *const list, int const pid)
{
	t_pid *const	node = pid_new(pid);

	if (!node)
		return (NULL);
	return (pid_lst_push_back(list, node));
}
