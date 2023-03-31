/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:12:16 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:16:23 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Allocate a new pid node and initialize its attributes.
 * 
 * @param	pid The process id to store in the node.
 * 
 * @return	A pointer to the newly allocated node, or NULL if an error occured. 
 */
t_pid	*pid_new(int const pid)
{
	t_pid *const	node = malloc(sizeof(t_pid));

	if (!node)
		return (NULL);
	node->pid = pid;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
