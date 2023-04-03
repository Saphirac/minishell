/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:37:40 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 17:55:59 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new token with the given parameter type and str.
 * 
 * @details Uses ft_strdup() for the str.
 * 
 * @param type of the new token.
 * @param str of the new token
 * @return t_token* pointer to the new node.
 */
t_token	*token_new(t_token_type const type, char *const str)
{
	t_token *const	output = malloc(sizeof(t_token));

	if (!output)
		return (NULL);
	output->type = type;
	output->str = ft_strdup(str);
	if (!output->str)
		return (NULL);
	output->next = NULL;
	output->prev = NULL;
	return (output);
}
