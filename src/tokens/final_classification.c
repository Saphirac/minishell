/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:25:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:10:49 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if token with T_COMMAND type is instead a T_BUILTIN.
 * 
 * @param tmp token with T_COMMAND to eventually retype.
 * @return T_COMMAND or T_BUILTIN.
 */
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

/**
 * @brief Parses token_lst and if a T_COMMAND is encountered,
 * check if it's a builtin instead.
 * If a T_PIPE is encountered, modify the is_pipeline bool to true.
 * 
 * @param token_lst list containing all tokens.
 * @param is_pipeline bool indicating if there is a pipe in the list.
 */
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

/**
 * @brief Checks if T_PIPE aren't in the beginning
 * or the end after tokens suppressions.
 * Also checks that T_PIPE aren't followed by another T_PIPE.
 * Checks if redirections are indeed followed by a T_FILE.
 * 
 * @param token_lst list to check.
 * @return EXIT_ERROR if syntax is incorrect and EXIT_SUCCESS else.
 */
int	final_syntax(t_token_lst *token_lst)
{
	t_token	*tmp;

	if (!token_lst->head)
		return (EXIT_SUCCESS);
	if (token_lst->head->type == T_PIPE || token_lst->tail->type == T_PIPE
		|| __is_redirection(token_lst->tail->type) == true)
		return (syntax_error(NULL));
	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->type == T_PIPE && tmp->next->type == T_PIPE)
			return (syntax_error(NULL));
		if (__is_redirection(tmp->type) == true
			&& tmp->next && tmp->next->type != T_FILE)
			return (syntax_error(NULL));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
