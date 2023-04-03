/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:12:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 05:48:01 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Execute a builtin, searching for its related function
 * 			in the builtin lookup table, and calling it. If an error occurs,
 * 			an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__run_builtin(t_shell *const shell)
{
	unsigned int	i;

	if (!env_lst_add_back(&shell->env, "QUIET_EXIT", NULL))
		return (g_exit_code = 1U, perror("env_lst_add_back()"), EXIT_FAILURE);
	i = 0U;
	while (ft_strcmp(shell->tokens.head->str, g_builtin[i].name))
		++i;
	return (g_builtin[i].func(&shell->env, shell->tokens.head->next));
}

/**
 * @brief	Search for a command in the PATH environment variable,
 * 			and replace the command string by its absolute path.
 * 			If none of the paths in PATH contains the command,
 * 			the command string is kept unchanged. If an error occurs,
 * 			an error message is output on stderr.
 * 
 * @param	cmd The command to search for.
 * @param	env The linked list containing the environment variables.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__search_in_path(
	char const **const cmd,
	t_env_lst const *const env)
{
	t_env *const	node = env_lst_get_one(env, "PATH");
	char const		**paths;
	char const		**dent;
	char const		*abs_path;

	if (!node || !node->value)
		return (EXIT_SUCCESS);
	paths = (char const **)ft_split(node->value, ":");
	if (!paths)
		return (g_exit_code = 1U, perror("ft_split()"), EXIT_FAILURE);
	dent = paths;
	while (*paths)
	{
		abs_path = ft_strlink((char const *const []){*paths, *cmd, NULL}, "/");
		if (!abs_path)
			return (g_exit_code = 1U, free(dent), perror("ft_strlink()"),
				EXIT_FAILURE);
		if (!access(abs_path, F_OK))
			return (free(dent), free((void *)*cmd), *cmd = abs_path,
				EXIT_SUCCESS);
		free((void *)abs_path);
		++paths;
	}
	return (free(dent), EXIT_SUCCESS);
}

/**
 * @brief	Prepend the current working directory to the command string,
 * 			and check if it refers to a file. If it does, replace the command
 * 			string by its absolute path. Otherwise, the command string is kept
 * 			unchanged. If an error occurs, an error message is output on stderr.
 * 
 * @param	cmd The command to search for.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__search_from_cwd(char const **const cmd)
{
	char const *const	cwd = getcwd(NULL, 0);
	char const			*abs_path;

	if (!cwd)
		return (g_exit_code = 1U, perror("getcwd()"), EXIT_FAILURE);
	abs_path = ft_strlink((char const *const []){cwd, *cmd, NULL}, "/");
	if (!abs_path)
		return (g_exit_code = 1U, free((void *)cwd), perror("ft_strlink()"),
			EXIT_FAILURE);
	free((void *)cwd);
	if (!access(abs_path, F_OK))
	{
		free((void *)*cmd);
		*cmd = abs_path;
	}
	else
		free((void *)abs_path);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Execute one command, replacing the current process by the new one.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	The function calls execve(), and therefore never returns,
 * 			except if an error occured, and then EXIT_FAILURE is returned.
 */
inline static int	__run_command(t_shell *const shell)
{
	char *const *const	av = token_lst_to_string_array(&shell->tokens);
	char *const *const	ep = env_lst_to_string_array(&shell->env);

	if (!av)
		return (g_exit_code = 1U, free((void *)ep),
			perror("token_lst_to_string_array()"), EXIT_FAILURE);
	if (!ep)
		return (g_exit_code = 1U, free((void *)av),
			perror("env_lst_to_string_array()"), EXIT_FAILURE);
	token_lst_clear(&shell->tokens);
	env_lst_clear(&shell->env);
	execve(av[0], av, ep);
	return (g_exit_code = 1U, free((void *)av), free((void *)ep),
		perror("execve()"), EXIT_FAILURE);
}

/**
 * @brief	Execute one command or builtin, searching for its absolute path
 * 			in the case of a command. If an error occurs,
 * 			an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	run(t_shell *const shell)
{
	if (!*shell->tokens.head->str)
		return (command_not_found_error(shell->tokens.head->str));
	if (!ft_strchr(shell->tokens.head->str, '/'))
	{
		if (shell->tokens.head->type == T_BUILTIN)
			return (__run_builtin(shell));
		if (__search_in_path((char const **)&shell->tokens.head->str,
				&shell->env))
			return (EXIT_FAILURE);
	}
	else if (__search_from_cwd((char const **)&shell->tokens.head->str))
		return (EXIT_FAILURE);
	if (*shell->tokens.head->str != '/')
		return (command_not_found_error(shell->tokens.head->str));
	if (access(shell->tokens.head->str, F_OK))
		return (no_such_file_or_directory_error(NULL, shell->tokens.head->str));
	if (is_directory(shell->tokens.head->str))
		return (is_a_directory_error(NULL, shell->tokens.head->str));
	if (access(shell->tokens.head->str, X_OK))
		return (permission_denied_error(shell->tokens.head->str));
	return (__run_command(shell));
}
