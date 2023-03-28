/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:25:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/28 20:51:51 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static t_token_type	__ft_cmd_or_builtin(t_token const *const tmp)
{
	unsigned int	i;

	i = 0U;
	while (g_builtin[i].name)
	{
		if (ft_strcmp(tmp->str, g_builtin[i].name) == 0)
			return (T_BUILTIN);
		++i;
	}
	return (T_COMMAND);
}

void	final_classification(t_token_lst *token_lst, bool *is_pipeline)
{
	t_token	*tmp;

	tmp = token_lst->head;
	*is_pipeline = false;
	while (tmp)
	{
		if (tmp->type == T_COMMAND)
			tmp->type = __ft_cmd_or_builtin(tmp);
		if (tmp->type == T_PIPE && *is_pipeline == false)
			*is_pipeline = true;
		tmp = tmp->next;
	}
}
