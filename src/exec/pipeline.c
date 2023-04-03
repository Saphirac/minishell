/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:10:16 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 05:45:06 by jodufour         ###   ########.fr       */
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
		return (g_exit_code = 1U, perror("fork()"), EXIT_FAILURE);
	if (pid)
	{
		if (!pid_lst_add_back(&shell->pids, pid))
			return (g_exit_code = 1U, kill(pid, SIGTERM),
				perror("pid_lst_add_back()"), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (close(shell->stdin_backup) || (pds[0] != STDIN_FILENO && close(pds[0])))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	token_lst_del_range(&shell->tokens, node, NULL);
	pid_lst_clear(&shell->pids);
	if (!pipe_redirection(pds[1]) && !file_redirections(&shell->tokens)
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
	if (pid_lst_wait(&shell->pids))
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
			return (g_exit_code = 1U, pid_lst_kill(&shell->pids, SIGTERM),
				perror("pipe()"), EXIT_FAILURE);
		if (__subprocess(shell, node, pds))
			return (close(pds[0]), close(pds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
		if (dup2(pds[0], STDIN_FILENO) == -1)
			return (g_exit_code = 1U, close(pds[0]), close(pds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), perror("dup2()"),
					EXIT_FAILURE);
		if (close(pds[0]) || close(pds[1]))
			return (g_exit_code = 1U,pid_lst_kill(&shell->pids, SIGTERM),
				perror("close()"), EXIT_FAILURE);
		token_lst_del_range(&shell->tokens, shell->tokens.head, node->next);
		node = token_lst_find_first_by_type(&shell->tokens, T_PIPE);
	}
	return (__last_command(shell, pds));
}
