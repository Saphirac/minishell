/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:28:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/02 04:06:59 by jodufour         ###   ########.fr       */
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
