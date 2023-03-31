/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:12:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/31 06:15:31 by jodufour         ###   ########.fr       */
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
		return (internal_error("env_lst_add_back()"));
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
		return (internal_error("ft_split()"));
	dent = paths;
	while (*paths)
	{
		abs_path = ft_strlink((char const *const []){*paths, *cmd, NULL}, "/");
		if (!abs_path)
			return (free(dent), internal_error("ft_strlink()"));
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
		return (internal_error("getcwd()"));
	abs_path = ft_strlink((char const *const []){cwd, *cmd, NULL}, "/");
	if (!abs_path)
		return (free((void *)cwd), internal_error("ft_strlink()"));
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
		return (free((void *)ep),
			internal_error("token_lst_to_string_array()"));
	if (!ep)
		return (free((void *)av), internal_error("env_lst_to_string_array()"));
	token_lst_clear(&shell->tokens);
	env_lst_clear(&shell->env);
	execve(av[0], av, ep);
	return (internal_error("execve()"));
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
		return (g_exit_code = 127U,
			command_not_found_error(shell->tokens.head->str));
	if (access(shell->tokens.head->str, F_OK))
		return (g_exit_code = 127U,
			no_such_file_or_directory_error(NULL, shell->tokens.head->str));
	if (access(shell->tokens.head->str, X_OK))
		return (g_exit_code = 126U,
			permission_denied_error(shell->tokens.head->str));
	return (__run_command(shell));
}
