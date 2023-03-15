/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:44:32 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/15 19:50:17 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief 	Modify the value of the given env node.
 * 			If an error occures during the modification,
 * 			the previous value is kept unchanged.
 * 
 * @param	node The node to modify.
 * @param	value The new value to set.
 * 
 * @return	EXIT_SUCCESS if the node was successfully modified, or
 * 			EXIT_FAILURE if an error occured.
 */
inline static int	__modify_ones_value(t_env *const node, char const *value)
{
	value = ft_strdup(value);
	if (!value)
		return (EXIT_FAILURE);
	free((void *)node->value);
	node->value = value;
	return (EXIT_SUCCESS);
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
		return (internal_error("export"));
	node = env_lst_get_one(env, id);
	if (node)
	{
		free((void *)id);
		if (*ptr && __modify_ones_value(node, ptr + 1))
			return (internal_error("export"));
		return (EXIT_SUCCESS);
	}
	(void)((*ptr && ++ptr) || (ptr = NULL));
	if (env_lst_add_back(env, id, ptr))
		return (free((void *)id), internal_error("export"));
	return (free((void *)id), EXIT_SUCCESS);
}
