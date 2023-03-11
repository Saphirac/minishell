/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:49:15 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 02:29:51 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Print the content of an env list to STDOUT_FILENO.
 * 
 * @param	list The list to print.
 */
void	env_lst_print(t_env_lst const *const list)
{
	t_env	*curr;

	curr = list->head;
	while (curr)
	{
		ft_putstr_fd(curr->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(curr->value, STDOUT_FILENO);
		curr = curr->next;
	}
}
