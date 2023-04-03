/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:10:16 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 02:09:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Create a subprocess, apply pipes redirections,
 * 			then apply input and output redirections,
 * 			and execute the given command/builtin.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * @param	node The first node of the token list containing a pipe.
 * @param	pds The two pipe descriptors
 * 			corresponding to the pipe following the command/builtin to run.
 * 
 * @return	In the subprocess, the function calls `exit()`,
 * 			and therefore never returns.
 * 			In the parent process, the function returns EXIT_SUCCESS,
 * 			or EXIT_FAILURE if an error occured.
 */
inline static int	__subprocess(
	t_shell *const shell,
	t_token const *const node,
	int const pds[2])
{
	int const	pid = fork();

	if (pid == -1)
		return (internal_error("fork()"));
	if (pid)
	{
		if (!pid_lst_add_back(&shell->pids, pid))
			return (kill(pid, SIGTERM), internal_error("pid_lst_add_back()"));
		return (EXIT_SUCCESS);
	}
	token_lst_del_range(&shell->tokens, node, NULL);
	pid_lst_clear(&shell->pids);
	if (close(shell->stdin_backup) || (pds[0] != STDIN_FILENO && close(pds[0])))
		return (internal_error("close()"));
	if (!signal_default() && !pipe_redirection(pds[1]) && !file_redirections(&shell->tokens)
		&& !g_exit_code && shell->tokens.size)
		run(shell);
	exit(g_exit_code);
}

/**
 * @brief	Execute the last command of a pipeline of commands/builtins
 * 			in a subprocess, applying input and output redirections only.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * @param	pds The two pipe descriptors
 * 			corresponding to the pipe following the command/builtin to run.
 * 
 * @return	
 */
inline static int	__last_command(t_shell *const shell, int pds[2])
{
	pds[0] = STDIN_FILENO;
	pds[1] = STDOUT_FILENO;
	if (__subprocess(shell, NULL, pds))
		return (pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
	if (close(STDIN_FILENO))
		return (g_exit_code = 1U, pid_lst_kill(&shell->pids, SIGTERM),
			perror("close()"), EXIT_FAILURE);
	if (signal_ignore() || pid_lst_wait(&shell->pids))
		return (pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Execute a pipeline of commands/builtins in subprocesses,
 * 			applying pipe redirections in a first time,
 * 			and input and output redirections in a second time.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * @param	node The first node of the token list containing a pipe.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pipeline(t_shell *const shell, t_token const *node)
{
	int	pds[2];

	while (node)
	{
		if (pipe(pds))
			return (pid_lst_kill(&shell->pids, SIGTERM),
				internal_error("pipe()"));
		if (__subprocess(shell, node, pds))
			return (close(pds[0]), close(pds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
		if (dup2(pds[0], STDIN_FILENO) == -1)
			return (close(pds[0]), close(pds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), internal_error("dup2()"));
		if (close(pds[0]) || close(pds[1]))
			return (pid_lst_kill(&shell->pids, SIGTERM),
				internal_error("close()"));
		token_lst_del_range(&shell->tokens, shell->tokens.head, node->next);
		node = token_lst_find_first_by_type(&shell->tokens, T_PIPE);
	}
	return (__last_command(shell, pds));
}