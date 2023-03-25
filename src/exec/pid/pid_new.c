/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:12:16 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 15:12:54 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid	*pid_new(int const pid)
{
	t_pid *const	new = malloc(sizeof(t_pid));

	if (!new)
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	return (new);
}
