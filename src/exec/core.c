/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:08:53 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 05:42:34 by jodufour         ###   ########.fr       */
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
		return (g_exit_code = 1U, ft_fddel(backup), perror("dup2()"),
			EXIT_FAILURE);
	if (ft_fddel(backup))
		return (g_exit_code = 1U, perror("ft_fddel()"), EXIT_FAILURE);
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
		return (g_exit_code = 1U, perror("dup()"), EXIT_FAILURE);
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
		return (g_exit_code = 1U, perror("dup()"), EXIT_FAILURE);
	g_exit_code = 0U;
	if (!shell->is_pipeline
		&& !token_lst_find_first_by_type(&shell->tokens, T_COMMAND))
	{
		if (__execute_in_place(shell))
			return (__restore_std(STDIN_FILENO, &shell->stdin_backup,
					EXIT_FAILURE));
	}
	else if (
		pipeline(shell, token_lst_find_first_by_type(&shell->tokens, T_PIPE)))
		return (__restore_std(STDIN_FILENO, &shell->stdin_backup,
				EXIT_FAILURE));
	return (__restore_std(STDIN_FILENO, &shell->stdin_backup, EXIT_SUCCESS));
}
