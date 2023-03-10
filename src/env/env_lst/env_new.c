/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:09:10 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 02:09:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "list.h"
#include <stdlib.h>

/**
 * @brief	Create a new env node.
 * 
 * @param	name The `name` attribute of the new node. 
 * @param	value The `value` attribute of the new node. 
 * 
 * @return	A pointer to the new node, or NULL if an error occured. 
 */
t_env	*env_new(char const *const name, char const *const value)
{
	t_env *const	output = malloc(sizeof(t_env));

	if (!output)
		return (NULL);
	output->name = ft_strdup(name);
	output->value = ft_strdup(value);
	if (!output->name || !output->value)
	{
		free(output->name);
		free(output->value);
		free(output);
		return (NULL);
	}
	output->next = NULL;
	output->prev = NULL;
	return (output);
}
