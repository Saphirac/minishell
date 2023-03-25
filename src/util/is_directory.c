/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:17:43 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/18 03:27:59 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Check if a pathname refers to a directory.
 * 
 * @param	pathname The pathname to check.
 * 
 * @return	true if the pathname refers to a directory, or false if not.
 */
bool	is_directory(const char *const pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf))
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}
