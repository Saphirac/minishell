/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:08:53 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 00:53:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Restore the standard input/output to their original file, and close
 * 			the backup file descriptor.
 * 
 * @param	std The standard file descriptor to restore.
 * @param	backup A reference to the file descriptor
 * 			used to preserve the original file.
 * @param	status The status to return if no errors occured while restoring
 * 			the standard input/output.
 * 
 * @return	The given `status`, or EXIT_FAILURE if an error occured.
 */
inline static int	__restore_std(
	int const std,
	int *const backup,
	int const status)
{
	if (dup2(*backup, std) == -1)
		return (ft_fddel(backup), perror("dup2()"), EXIT_FAILURE);
	if (ft_fddel(backup))
		return (perror("ft_fddel()"), EXIT_FAILURE);
	return (status);
}

/**
 * @brief	Proceed to the execution of the command line in the same process as
 * 			the shell. This should occurs only when the commandline contains at
 * 			most one command to run, and this command is a builtin.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
inline static int	__execute_in_place(t_shell *const shell)
{
	unsigned int	i;

	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdout_backup == -1)
		return (perror("dup()"), EXIT_FAILURE);
	if (file_redirections(&shell->tokens))
		return (__restore_std(STDOUT_FILENO, &shell->stdout_backup,
				EXIT_FAILURE));
	if (g_exit_code || !shell->tokens.size)
		return (__restore_std(STDOUT_FILENO, &shell->stdout_backup,
				EXIT_SUCCESS));
	i = 0U;
	while (g_builtin[i].name
		&& ft_strcmp(g_builtin[i].name, shell->tokens.head->str))
		++i;
	if (g_builtin[i].func
		&& g_builtin[i].func(&shell->env, shell->tokens.head->next))
		return (__restore_std(STDOUT_FILENO, &shell->stdout_backup,
				EXIT_FAILURE));
	return (__restore_std(STDOUT_FILENO, &shell->stdout_backup, EXIT_SUCCESS));
}

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
	if (close(shell->stdin_backup) || (pds[0] != STDIN_FILENO && close(pds[0])))
		return (internal_error("close()"));
	token_lst_del_range(&shell->tokens, node, NULL);
	pid_lst_clear(&shell->pids);
	if (!pipe_redirection(pds[1]) && !file_redirections(&shell->tokens)
		&& !g_exit_code && shell->tokens.size)
		run(shell);
	exit(g_exit_code);
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
inline static int	__pipeline(t_shell *const shell, t_token const *node)
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
	pds[0] = STDIN_FILENO;
	pds[1] = STDOUT_FILENO;
	if (__subprocess(shell, NULL, pds) || pid_lst_wait(&shell->pids))
		return (pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
	return (pid_lst_clear(&shell->pids), EXIT_SUCCESS);
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
	shell->stdin_backup = dup(STDIN_FILENO);
	if (shell->stdin_backup == -1)
		return (internal_error("dup()"));
	g_exit_code = 0U;
	if (!shell->is_pipeline
		&& !token_lst_find_first_by_type(&shell->tokens, T_COMMAND))
	{
		if (__execute_in_place(shell))
			return (__restore_std(STDIN_FILENO, &shell->stdin_backup,
					EXIT_FAILURE));
	}
	else if (
		__pipeline(shell, token_lst_find_first_by_type(&shell->tokens, T_PIPE)))
		return (__restore_std(STDIN_FILENO, &shell->stdin_backup,
				EXIT_FAILURE));
	return (__restore_std(STDIN_FILENO, &shell->stdin_backup, EXIT_SUCCESS));
}
