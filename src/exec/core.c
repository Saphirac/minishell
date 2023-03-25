/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:08:53 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 05:07:35 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int	__subprocess(
	t_shell *const shell,
	t_token const *const node,
	int const pipe_out)
{
	return (EXIT_SUCCESS);
}

/**
 * @brief	Execute a pipeline of commands/builtins in subprocesses,
 * 			applying pipe redirections in a first time,
 * 			and input and output redirections in a second time.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__pipeline(t_shell *const shell, t_token const *node)
{
	int	fds[3];

	fds[2] = dup(STDIN_FILENO);
	if (fds[2] == -1)
		return (internal_error("dup()"));
	while (node)
	{
		if (pipe(fds))
			return (close(fds[2]), pid_lst_kill(&shell->pids, SIGTERM),
				internal_error("pipe()"));
		if (__subprocess(shell, node, fds[1]))
			return (close(fds[0]), close(fds[1]), close(fds[2]),
				pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
		token_lst_del_range(&shell->tokens, shell->tokens.head, node->next);
		node = token_lst_find_first_by_type(&shell->tokens, T_PIPE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Execute a builtin with no pipes in the same process as the shell.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__builtin_alone(t_shell *const shell)
{
	size_t	i;

	i = 0LU;
	while (ft_strcmp(g_builtin[i].name, shell->tokens.head->str))
		++i;
	return (g_builtin[i].func(&shell->env, shell->tokens.head->next));
}

/**
 * @brief	Proceed to the execution of the given commands/builtins,
 * 			using subprocess except when running a builtin with no pipes,
 * 			applying input, output, and pipes redirections.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	execution(t_shell *const shell)
{
	t_token const *const	node
		= token_lst_find_first_by_type(&shell->tokens, T_PIPE);

	if (node || !token_lst_is_first_builtin(&shell->tokens))
		return (__pipeline(shell, node));
	return (__builtin_alone(shell));
}
