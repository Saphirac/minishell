/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_curpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:42:21 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 05:28:34 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Check whether the given path has to be searched in CDPATH.
 * 
 * @param	path The path to check.
 * 
 * @return	True if the given path has to be searched in CDPATH,
 * 			or false if not.
 */
inline static bool	__is_possibly_cdpath(char const *path)
{
	*path == '.' && ++path;
	*path == '.' && ++path;
	return (*path && *path != '/');
}

/**
 * @brief	Allocate and set a new absolute path
 * 			using a pathname from the `CDPATH` environment variable as prefix,
 * 			and a relative pathname from the user input as suffix.
 * 			If an error occurs during the process,
 * 			then an error message is output on stderr.
 * 
 * @param	prefix The pathname from `CDPATH` to join as a prefix.
 * @param	prefix_len The length of the prefix.
 * @param	suffix The relative pathname to join as a suffix.
 * @param	suffix_len The length of the suffix.
 * 
 * @return	An allocated string containing the two joined pathes,
 * 			or NULL if an error occured.
 */
inline static char	*__prepend_cdpath_pathname(
	char const *const prefix,
	size_t const prefix_len,
	char const *const suffix,
	size_t const suffix_len)
{
	char	*path;

	if (!prefix_len)
	{
		path = malloc((2LU + suffix_len + 1LU) * sizeof(char));
		if (!path)
			return (perror("cd: malloc()"), NULL);
		ft_memcpy(path, "./", 2LU);
		ft_memcpy(path + 2LU, suffix, suffix_len);
		path[2LU + suffix_len] = 0;
		return (path);
	}
	path = malloc((prefix_len + 1LU + suffix_len + 1LU) * sizeof(char));
	if (!path)
		return (perror("cd: malloc()"), NULL);
	ft_memcpy(path, prefix, prefix_len);
	path[prefix_len] = '/';
	ft_memcpy(path + prefix_len + 1LU, suffix, suffix_len);
	path[prefix_len + 1LU + suffix_len] = 0;
	return (path);
}

/**
 * @brief	Try to match an existing destination directory concatenating pathes
 * 			contained in the `CDPATH` environment variable if any.
 * 			If a match is found, the given `curpath` is set to it.
 * 			Else, the given `curpath` is set to NULL.
 * 			If an error occurs during the process,
 * 			then an error message is output on stderr.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	dir The string representing the new current working directory.
 * @param	dir_len The length of the string representing the new current
 * 			working directory.
 * @param	curpath A reference to the curpath to set.
 * 
 * @return	EXIT_SUCCESS, no matter if a match has been found or not,
 * 			or EXIT_FAILURE if an error occured.
 */
inline static int	__try_cdpath(
	t_env_lst const *const env,
	char const *const dir,
	size_t const dir_len,
	char **const curpath)
{
	t_env const *const	node = env_lst_get_one(env, "CDPATH");
	char const			*ptr0;
	char const			*ptr1;

	if (!node || !node->value)
		return (*curpath = NULL, EXIT_SUCCESS);
	ptr0 = node->value;
	while (*ptr0)
	{
		ptr1 = ft_strchr(ptr0, ':');
		if (!ptr1)
			ptr1 = ptr0 + ft_strlen(ptr0);
		*curpath = __prepend_cdpath_pathname(ptr0, ptr1 - ptr0, dir, dir_len);
		if (!*curpath)
			return (EXIT_FAILURE);
		if (is_directory(*curpath))
			return (EXIT_SUCCESS);
		free(*curpath);
		ptr0 = ptr1 + !!*ptr1;
	}
	return (*curpath = NULL, EXIT_SUCCESS);
}

/**
 * @brief	Allocate and set a new absolute path
 * 			using the current working directory as prefix,
 * 			and a relative pathname from the user input as suffix.
 * 			If an error occures during the process,
 * 			then an error message is output on stderr.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	dir The string representing the new current working directory.
 * @param	dir_len The length of the string representing the new current
 * 			working directory.
 * @param	curpath A reference to the curpath to set.
 * 
 * @return	An allocated string containing the two joined pathes,
 * 			or NULL if an error occured.
 */
inline static char	*__prepend_cwd_pathname(
	char const *const dir,
	size_t const dir_len,
	char **const curpath)
{
	char const	*cwd;
	size_t		cwd_len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: getcwd()"), NULL);
	cwd_len = ft_strlen(cwd);
	*curpath = malloc((cwd_len + 1LU + dir_len + 1LU) * sizeof(char));
	if (!*curpath)
		return (perror("cd: malloc()"), NULL);
	ft_memcpy(*curpath, cwd, cwd_len);
	free((void *)cwd);
	(*curpath)[cwd_len] = '/';
	ft_memcpy(*curpath + cwd_len + 1LU, dir, dir_len + 1LU);
	return (*curpath);
}

/**
 * @brief	Determine and allocate the raw value of the string
 * 			representing the new current working directory,
 * 			but as an absolute path only.
 * 			If an error occurs during the process,
 * 			then an error message is output on stderr.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	dir The string representing the new current working directory.
 * 
 * @return	The raw value of the string representing the new current working
 * 			directory, or NULL if an error occured.
 */
char	*raw_curpath(
	t_env_lst const *const env,
	char const *const dir)
{
	size_t const	dir_len = ft_strlen(dir);
	char			*curpath;

	curpath = NULL;
	if (*dir == '/')
	{
		curpath = ft_strdup(dir);
		if (!curpath)
			return (perror("cd: ft_strdup()"), NULL);
		return (curpath);
	}
	if (__is_possibly_cdpath(dir) && __try_cdpath(env, dir, dir_len, &curpath))
		return (NULL);
	if (curpath)
		return (curpath);
	return (__prepend_cwd_pathname(dir, dir_len, &curpath));
}
