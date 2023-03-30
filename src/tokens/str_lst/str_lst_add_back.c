/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:43:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/27 17:28:30 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_lst_add_back(t_str_lst *const list, char *const str, bool is_quoted)
{
	t_str *const	node = str_new(str, is_quoted);

	if (!node)
		return (EXIT_FAILURE);
	str_lst_push_back(list, node);
	return (EXIT_SUCCESS);
}
