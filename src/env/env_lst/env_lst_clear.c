/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:36:05 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:08:00 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief	Remove every node from an env list,
 * 			clearing its stored data, and releasing its related memory.
 * 
 * @param	list The list to clear.
 */
void	env_lst_clear(t_env_lst *const list)
{
	while (list->size)
		env_lst_del_one(list, list->head);
}
