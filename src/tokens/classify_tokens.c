/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:28:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/30 02:07:54 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	classify_tokens(t_shell *shell)
{
	t_token	*tmp;
	bool	cmd;

	tmp = shell->tokens.head;
	cmd = false;
	if (!tmp || !tmp->str)
		return (EXIT_ERROR);
	if (tmp->str[0] == '|')
		return (printf("syntax error.\n"),
			EXIT_ERROR);
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
