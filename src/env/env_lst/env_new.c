/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:09:10 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 18:09:25 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env *const	node = malloc(sizeof(t_env));

	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	if (!node->name || (value && !node->value))
	{
		free((void *)node->name);
		free((void *)node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
