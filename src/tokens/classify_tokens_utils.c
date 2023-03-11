/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:18:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/11 03:22:09 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_if_pipe(t_token *tmp, bool *cmd)
{
	tmp->type = T_PIPE;
	if (!tmp->next || tmp->next->str[0] == '|')
		return (printf("syntax error.\n"),
			EXIT_ERROR);
	tmp = tmp->next;
	*cmd = false;
	if (tmp && tmp->type == T_WORD)
	{
		tmp->type = T_COMMAND;
		*cmd = true;
		return (ft_if_command(tmp, cmd));
	}
	else if (tmp->type == T_OPERATOR)
		return (ft_if_operator(tmp, cmd));
	return (EXIT_SUCCESS);
}

int	ft_if_heredoc(t_token *tmp, bool *cmd)
{
	tmp->type = T_HEREDOC;
	tmp = tmp->next;
	tmp->type = T_DELIMITER;
	tmp = tmp->next;
	if (!tmp)
		return (EXIT_SUCCESS);
	if (tmp->type == T_WORD && *cmd == false)
	{
		tmp->type = T_COMMAND;
		*cmd = true;
		return (ft_if_command(tmp, cmd));
	}
	else if (tmp->type == T_WORD && *cmd == true)
	{
		tmp->type = T_ARGUMENT;
		return (ft_if_command(tmp, cmd));
	}
	else if (tmp->str[0] == '|')
		return (ft_if_pipe(tmp, cmd));
	else if (tmp->type == T_OPERATOR)
		return (ft_if_operator(tmp, cmd));
	return (EXIT_SUCCESS);
}

int	ft_if_output_input(t_token *tmp, bool *cmd)
{
	tmp = tmp->next;
	tmp->type = T_FILE;
	tmp = tmp->next;
	if (!tmp)
		return (EXIT_SUCCESS);
	if (tmp->type == T_WORD && *cmd == false)
	{
		tmp->type = T_COMMAND;
		*cmd = true;
		return (ft_if_command(tmp, cmd));
	}
	else if (tmp->type == T_WORD && *cmd == true)
	{
		tmp->type = T_ARGUMENT;
		return (ft_if_command(tmp, cmd));
	}
	else if (tmp->str[0] == '|')
		return (ft_if_pipe(tmp, cmd));
	else if (tmp->type == T_OPERATOR)
		return (ft_if_operator(tmp, cmd));
	return (EXIT_SUCCESS);
}

int	ft_if_operator(t_token *tmp, bool *cmd)
{
	if (!tmp->next || tmp->next->type != T_WORD)
		return (printf("syntax error.\n"), EXIT_ERROR);
	if (ft_strcmp(tmp->str, "<<") == 0)
		return (ft_if_heredoc(tmp, cmd));
	else
	{
		if (ft_strcmp(tmp->str, ">>") == 0)
			tmp->type = T_OUTPUT_APPEND;
		else if (tmp->str[0] == '>')
			tmp->type = T_OUTPUT_TRUNCATE;
		else if (tmp->str[0] == '<')
			tmp->type = T_INPUT;
		return (ft_if_output_input(tmp, cmd));
	}
	return (EXIT_SUCCESS);
}

int	ft_if_command(t_token *tmp, bool *cmd)
{
	tmp = tmp->next;
	while (tmp && tmp->type == T_WORD)
	{
		tmp->type = T_ARGUMENT;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp->str[0] == '|')
			return (ft_if_pipe(tmp, cmd));
		else
			return (ft_if_operator(tmp, cmd));
	}
	return (EXIT_SUCCESS);
}
