/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_curpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:42:21 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/22 04:31:16 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Try to retrieve the current working directory from the environment.
 * 			If it fails, try to retrieve it from the system.
 * 			If an error occures during the process, an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * 
 * @return	An allocated string containing the current working directory,
 * 			or NULL if an error occured.
 */
inline static char	*__cwd(t_env_lst const *const env)
{
	char		*cwd;
	t_env const	*node;

	node = env_lst_get_one(env, "PWD");
	if (!node || !*node->value)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (internal_error("cd: getcwd"), NULL);
	}
	else
	{
		cwd = ft_strdup(node->value);
		if (!cwd)
			return (internal_error("cd: ft_strdup"), NULL);
	}
	return (cwd);
}

/**
 * @brief	Determine the raw value of the string representing the new current
 * 			working directory, but as an absolute path only.
 * 			If an error occures during the process, an error is output.
 * 
 * @param	dir The string representing the new current working directory.
 * 
 * @return	The raw value of the string representing the new current working
 * 			directory, or NULL if an error occured.
 */
char	*raw_curpath(
	t_env_lst const *const env,
	char const *const dir)
{
	char	*curpath;
	char	*cwd;

	if (*dir == '/')
	{
		curpath = ft_strdup(dir);
		if (!curpath)
			return (internal_error("cd: ft_strdup"), NULL);
		return (curpath);
	}
	cwd = __cwd(env);
	if (!cwd)
		return (NULL);
	curpath = NULL;
	return (free(cwd), curpath);
}
