/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:37:40 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/19 19:04:00 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
