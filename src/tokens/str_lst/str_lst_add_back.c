/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:43:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:57:04 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add a new node to the end of str_lst list.
 * 
 * @param list the list we add a node to.
 * @param str string of the new node.
 * @param is_quoted bool determining if node is quoted or not.
 * @return t_str* pointer to the new node.
 */
t_str	*str_lst_add_back(
	t_str_lst *const list,
	char *const str,
	bool is_quoted)
{
	t_str *const	node = str_new(str, is_quoted);

	if (!node)
		return (NULL);
	return (str_lst_push_back(list, node));
}
