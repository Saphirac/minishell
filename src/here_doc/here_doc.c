/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/04/02 04:50:58 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int	__expand_hd(t_env_lst *env, char **ret)
{
	int	i;

	i = 0;
	while ((*ret)[i])
	{
		if ((*ret)[i] == '$')
			return (search_env(env, ret));
		i++;
	}
	return (EXIT_SUCCESS);
}

inline static int	__get_hd(t_token *token, t_env_lst *env)
{
	char	*ret;
	char	*line;

	ret = ft_ctoa(0);
	if (!ret)
		return (EXIT_FAILURE);
	line = readline("> ");
	if (!line)
		return (write(STDERR_FILENO, "Unexpected eof\n", 15), EXIT_FAILURE);
	while (line && ft_strcmp(line, token->str))
	{
		if (stock_hd(line, &ret) == EXIT_FAILURE)
			return (free(line), free(ret), EXIT_FAILURE);
		free(line);
		line = readline("> ");
	}
	if (!line)
		return (free(ret),
			write(STDERR_FILENO, "Unexpected eof\n", 15), EXIT_FAILURE);
	free(line);
	if (ret && token->type != T_DELIMITER_QUOTED)
		if (__expand_hd(env, &ret) == EXIT_FAILURE)
			return (free(ret), EXIT_FAILURE);
	return (free(token->str), token->str = ret, EXIT_SUCCESS);
}

int	do_here_doc(t_token_lst *token_lst, t_env_lst *env)
{
	t_token	*tmp;

	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->type == T_DELIMITER || tmp->type == T_DELIMITER_QUOTED)
			if (__get_hd(tmp, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
