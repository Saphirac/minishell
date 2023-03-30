/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:43:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/19 19:38:12 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_lst_add_back(t_token_lst *const list, t_token_type const type,
	char *const str)
{
	t_token *const	node = token_new(type, str);

	if (!node)
		return (EXIT_FAILURE);
	token_lst_push_back(list, node);
	return (EXIT_SUCCESS);
}
