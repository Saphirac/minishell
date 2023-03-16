/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_print_assigned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:49:15 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/13 16:58:43 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Print all assigned variables contained in an env list
 * 			to standard output.
 * 
 * @param	list The list to print.
 */
void	env_lst_print_assigned(t_env_lst const *const list)
{
	t_env	*curr;

	curr = list->head;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd(curr->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(curr->value, STDOUT_FILENO);
		}
		curr = curr->next;
	}
}
