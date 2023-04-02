/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:36:17 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 03:33:56 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Remove every dot component and any <slash> characters
 * 			that separate them from the next component
 * 			from the given destination path.
 * 
 * @details	For example:
 * 			`/home/jodufour/.` becomes `/home/jodufour/`
 * 			`/home/jodufour/./.` becomes `/home/jodufour/`
 * 			`/home/./jodufour` becomes `/home/jodufour`
 * 
 * @param	curpath The destination path to remove dot-slash components from.
 * @param	end A reference to a pointer to the post-last character
 * 			of the `curpath` string.
 */
inline static void	__remove_dot_components(char *curpath, char **const end)
{
	char	*ptr0;
	char	*ptr1;

	ptr0 = ft_strstr(curpath, "/./");
	while (ptr0)
	{
		ptr1 = ptr0 + 3;
		while (*ptr1 == '/')
			++ptr1;
		ft_memmove(ptr0 + 1, ptr1, *end - ptr1);
		*end -= ptr1 - ptr0 - 1;
		ptr0 = ft_strstr(ptr0, "/./");
	}
	if (*end - curpath > 2 && !ft_strcmp(*end - 3, "/."))
	{
		--*end;
		(*end)[-1] = 0;
	}
}

/**
 * @brief 	If the given destination path ends with a dot-dot component,
 * 			then check whether the previous component refers to a directory.
 * 			If it does, then the dot-dot component and its previous component
 * 			are removed. Otherwise, an error message is output on stderr,
 * 			and the function ends.
 * 
 * @param	curpath The destination path
 * 			to remove trailing dot-dot component from.
 * @param	end A reference to a pointer to the post-last character
 * 			of the `curpath` string.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__remove_trailing_dot_dot_component(
	char *const curpath,
	char **const end)
{
	if (*end - curpath < 4 || ft_strcmp(*end - 4, "/.."))
		return (EXIT_SUCCESS);
	*end -= 4;
	while (*end > curpath && **end == '/')
		--*end;
	if (curpath < *end)
	{
		(*end)[1] = 0;
		if (access(curpath, F_OK))
			return (no_such_file_or_directory_error("cd", curpath));
		if (!is_directory(curpath))
			return (not_a_directory_error("cd", curpath));
		while (*end > curpath && **end != '/')
			--*end;
	}
	*end += 2;
	(*end)[-1] = 0;
	return (EXIT_SUCCESS);
}

/**
 * @brief 	Whenever a dot-dot component is encountered,
 * 			check whether the previous component refers to a directory.
 * 			If it does, then the dot-dot component and its previous component
 * 			are removed. Otherwise, an error message is output on stderr,
 * 			and the function ends.
 * 
 * @param	curpath The destination path
 * 			to remove dot-dot components from.
 * @param	end A reference to a pointer to the post last character
 * 			of the `curpath` string.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured. 
 */
inline static int	__remove_dot_dot_components(
	char *const curpath,
	char **const end,
	char *ptr0,
	char *ptr1)
{
	ptr0 = ft_strstr(curpath, "/../");
	while (ptr0)
	{
		ptr1 = ptr0;
		while (ptr1 > curpath && *ptr1 == '/')
			--ptr1;
		while (ptr1 > curpath && *ptr1 != '/')
			--ptr1;
		if (ptr1 < ptr0)
		{
			*ptr0 = 0;
			if (access(curpath, F_OK))
				return (no_such_file_or_directory_error("cd", curpath));
			if (!is_directory(curpath))
				return (not_a_directory_error("cd", curpath));
		}
		ptr0 += 3;
		while (*ptr0 == '/')
			++ptr0;
		ft_memmove(ptr1 + 1, ptr0, *end - ptr0);
		*end -= ptr0 - ptr1 - 1;
		ptr0 = ft_strstr(ptr1, "/../");
	}
	return (__remove_trailing_dot_dot_component(curpath, end));
}

/**
 * @brief 	Remove all the unnecessary <slash> characters from the given path.
 * 			
 * @details	Are considered unnecessary <slash> characters:
 * 			- Any non-leading consecutive <slash> characters.
 * 			- Any non-leading trailing <slash> characters.
 * 
 * @param	curpath The destination path to remove unnecessary slashes from.
 * @param	end A reference to a pointer to the post-last character
 */
inline static void	__remove_unnecessary_slash_characters(
	char *curpath,
	char **const end)
{
	char	*ptr0;
	char	*ptr1;

	ptr0 = ft_strstr(curpath, "//");
	while (ptr0)
	{
		ptr1 = ptr0 + 2;
		while (*ptr1 == '/')
			++ptr1;
		ft_memmove(ptr0 + 1, ptr1, *end - ptr1);
		*end -= ptr1 - ptr0 - 1;
		ptr0 = ft_strstr(ptr0, "//");
	}
	if (*end - curpath > 2 && (*end)[-2] == '/')
	{
		--*end;
		(*end)[-1] = 0;
	}
}

/**
 * @brief 	Convert the given destination path to a canonical form.
 * 			If an error occurs during the conversion,
 * 			then the value of the `curpath` string is unspecified,
 * 			and an error message is output on stderr.
 * 
 * @param	curpath The destination path to convert.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	canonicalize(char *const curpath)
{
	char	*end;

	end = curpath + ft_strlen(curpath) + 1;
	__remove_dot_components(curpath, &end);
	if (__remove_dot_dot_components(curpath, &end, NULL, NULL))
		return (EXIT_FAILURE);
	__remove_unnecessary_slash_characters(curpath, &end);
	return (EXIT_SUCCESS);
}
