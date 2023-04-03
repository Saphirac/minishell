/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/04/03 04:38:40 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	__handle_signal_hd(int const sig __attribute__((unused)))
{
	g_exit_code = 42;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	if (close(STDIN_FILENO))
		perror("close() failed.\n");
}

inline static int	__signal_heredoc(void)
{
	if (signal(SIGINT, &__handle_signal_hd) == SIG_ERR)
		return (perror("signal() failed"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
	while (line && ft_strcmp(line, token->str) && g_exit_code != 42)
	{
		if (stock_hd(line, &ret) == EXIT_FAILURE)
			return (free(line), free(ret), EXIT_FAILURE);
		free(line);
		line = readline("> ");
	}
	if (g_exit_code == 42)
		return (free(ret), g_exit_code = 130, EXIT_ERROR);
	if (!line)
		return (free(token->str), token->str = ret,
			write(STDERR_FILENO, "Unexpected eof\n", 15),
			token->type = T_CONTENT, EXIT_SUCCESS);
	if (ret && token->type != T_DELIMITER_QUOTED)
		if (__expand_hd(env, &ret) == EXIT_FAILURE)
			return (free(ret), free(line), EXIT_FAILURE);
	return (free(line), free(token->str), token->str = ret,
		token->type = T_CONTENT, EXIT_SUCCESS);
}

int	do_here_doc(t_token_lst *token_lst, t_env_lst *env)
{
	t_token		*tmp;
	int			exit_code;
	int const	fd = dup(STDIN_FILENO);

	if (fd == -1)
		return (perror("dup() failed.\n"), EXIT_FAILURE);
	tmp = token_lst->head;
	if (__signal_heredoc() == EXIT_FAILURE)
		return (dup2(fd, STDIN_FILENO), EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->type == T_DELIMITER || tmp->type == T_DELIMITER_QUOTED)
		{
			exit_code = __get_hd(tmp, env);
			if (exit_code != EXIT_SUCCESS)
				return (dup2(fd, STDIN_FILENO), close(fd), exit_code);
		}
		tmp = tmp->next;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2() failed\n"), close(fd), EXIT_FAILURE);
	if (close(fd))
		return (perror("close() failed\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
