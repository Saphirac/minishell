/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:25:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/01 00:07:04 by mcourtoi         ###   ########.fr       */
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

inline static bool	__is_redirection(t_token_type type)
{
	if (type == T_INPUT || type == T_OUTPUT_TRUNCATE || type == T_OUTPUT_APPEND)
		return (true);
	return (false);
}

int	final_syntax(t_token_lst *token_lst)
{
	t_token	*tmp;

	if (!token_lst->head)
		return (EXIT_SUCCESS);
	if (token_lst->head->type == T_PIPE || token_lst->tail->type == T_PIPE
		|| __is_redirection(token_lst->tail->type) == true)
		return (printf("Syntax error.\n"), EXIT_ERROR);
	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->type == T_PIPE && tmp->next->type == T_PIPE)
			return (printf("Syntax error.\n"), EXIT_ERROR);
		if (__is_redirection(tmp->type) == true
			&& tmp->next && tmp->next->type != T_FILE)
			return (printf("Syntax error.\n"), EXIT_ERROR);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
