/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/04/01 19:51:47 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_hd(t_token *token)
{	
	char	*ret;
	char	*line;

	line = readline("> ");
	if (!line)
		return (write(STDOUT_FILENO, "exit\n", 5), EXIT_FAILURE);
	while (line && ft_strcmp(line, token->str))
	{
		if (!stock_hd(line, &ret))
			return (free(line), EXIT_FAILURE);
		free(line);
		line = readline("> ");
	}
	if (token->type != T_DELIMITER_QUOTED)
		if (expand_heredoc(&ret) == EXIT_FAILURE)
			return (free(line), EXIT_FAILURE);
	free(token->str);
	token->str = ret;
	return (free(line), EXIT_SUCCESS);
}
