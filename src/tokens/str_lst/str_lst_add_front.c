/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:35:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 21:07:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	*str_lst_add_front(
	t_str_lst *const list,
	char *const str,
	bool is_quoted)
{
	t_str *const	node = str_new(str, is_quoted);

	if (!node)
		return (NULL);
	return (str_lst_push_front(list, node));
}
