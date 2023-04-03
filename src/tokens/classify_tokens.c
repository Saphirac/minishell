/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:28:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:12:38 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses tokens_lst list.
 * Classify each encountered nodes with their types depending on :
 * their position, type of the precedent node,
 * their actual type (T_OPERATOR / T_WORD).
 * 
 * @param shell struct containing tokens list.
 * @return EXIT_ERROR if syntax error and EXIT_SUCCESS else.
 */
int	classify_tokens(t_shell *shell)
{
	t_token	*tmp;
	bool	cmd;

	tmp = shell->tokens.head;
	cmd = false;
	if (!tmp || !tmp->str)
		return (EXIT_ERROR);
	if (tmp->str[0] == '|')
		return (syntax_error(NULL));
	if (tmp->type == T_WORD)
	{
		tmp->type = T_COMMAND;
		cmd = true;
		return (ft_if_command(tmp, &cmd));
	}
	else if (tmp->type == T_OPERATOR)
		return (ft_if_operator(tmp, &cmd));
	return (EXIT_SUCCESS);
}
