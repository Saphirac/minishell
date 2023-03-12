/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:44:32 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 23:47:21 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_ones_value(t_env *const node, char const *const value)
	__attribute__((nonnull));

/**
 * @brief	Check if the given identifier is valid.
 * 
 * @param	ptr The identifier to check.
 * 
 * @return	true if the identifier is valid, false otherwise.
 */
inline static bool	__is_valid_identifier(char const **const ptr)
{
	if (!ft_isalpha(**ptr) && **ptr != '_')
		return (false);
	++*ptr;
	while (**ptr && **ptr != '=')
	{
		if (!ft_isalnum(**ptr) && **ptr != '_')
			return (false);
		++*ptr;
	}
	return (true);
}

/**
 * @brief	Output an iternal error message.
 * 
 * @param	msg The message to output.
 * 
 * @return	Always EXIT_FAILURE.
 */
inline static int	__internal_error(void)
{
	ft_putendl_fd("export: internal error", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/**
 * @brief	Ouput an error related to an invalid identifier.
 * 
 * @param	id The invalid identifier.
 * 
 * @return	Always EXIT_FAILURE.
 */
inline static int	__invalid_identifier_error(char const *const id)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/**
 * @brief	Process one environment variable to add/modify.
 * 			If the identifier syntax is invalid, an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	str The variable to add/modify and its new value as a raw string,
 * 			formatted as "identifier=value".
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	process_one(t_env_lst *const env, char const *const str)
{
	char const	*ptr = str;
	char const	*id;
	t_env		*node;

	if (!__is_valid_identifier(&ptr))
		return (__invalid_identifier_error(str));
	id = ft_strndup(str, ptr - str);
	if (!id)
		return (__internal_error());
	node = env_lst_get_one(env, id);
	if (node)
	{
		free((void *)id);
		if (*ptr && modify_ones_value(node, ptr + 1))
			return (__internal_error());
	}
	else
	{
		if (*ptr)
			++ptr;
		else
			ptr = NULL;
		if (env_lst_add_back(env, id, ptr))
			return (free((void *)id), __internal_error());
	}
	return (free((void *)id), EXIT_SUCCESS);
}
