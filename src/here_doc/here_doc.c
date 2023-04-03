/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/04/03 19:10:16 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief If sigint is received, modify g_exit_code to 42 (arbitrary number). 
 */
inline static void	__handle_signal_hd(int const sig __attribute__((unused)))
{
	g_exit_code = 42;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	if (close(STDIN_FILENO))
		perror("close()");
}

/**
 * @brief Calls __handle_signal_hd() if SIGINT is received.
 * 
 * @return EXIT_FAILURE if signal() failed, EXIT_SUCCESS else. 
 */
inline static int	__signal_heredoc(void)
{
	if (signal(SIGINT, &__handle_signal_hd) == SIG_ERR)
		return (perror("signal()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief If heredoc delimiter is unquoted and a $ is found,
 * 	remplaces it with its env value.
 * 
 * @param env list containing the env variables.
 * @param ret heredoc result.
 * @return EXIT_FAILURE if search_env() fails, EXIT_SUCCESS else.
 */
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

/**
 * @brief Get the input from the user after a '<<' operator.
 * Stops when token->str is encountered.
 * Expands the heredoc if token->type is T_DELIMITER.
 * Remplace the str of token with this input.
 * 
 * @param token containing the delimiter.
 * @param env list containing env variables.
 * @return EXIT_FAILURE if malloc fails,
 * 	EXIT_ERROR if eof is encountered and EXIT_SUCCESS else.
 */
inline static int	__get_hd(t_token *token, t_env_lst *env)
{
	char	*ret;
	char	*line;

	ret = ft_ctoa(0);
	if (!ret)
		return (EXIT_FAILURE);
	line = readline("> ");
	while (line && ft_strcmp(line, token->str))
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

/**
 * @brief Parse token_lst, if a token->type is T_DELIMITER or T_DELIMITER_QUOTED,
 * launch get_hd() to get the user input.
 * Setup the signal_heredoc() function for the rest of the hd.
 * Create a fd for the heredoc reading and closes it at the end.
 * 
 * @param token_lst list containing all tokens. 
 * @param env list containing all env variables.
 * @return EXIT_FAILURE, EXIT_ERROR or EXIT_SUCCESS.
 */
int	do_here_doc(t_token_lst *token_lst, t_env_lst *env)
{
	t_token		*tmp;
	int			exit_code;
	int const	fd = dup(STDIN_FILENO);

	if (fd == -1)
		return (perror("dup()"), EXIT_FAILURE);
	tmp = token_lst->head;
	if (__signal_heredoc() == EXIT_FAILURE)
		return (dup2(fd, STDIN_FILENO), close(fd), EXIT_FAILURE);
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
		return (perror("dup2()"), close(fd), EXIT_FAILURE);
	if (close(fd))
		return (perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
