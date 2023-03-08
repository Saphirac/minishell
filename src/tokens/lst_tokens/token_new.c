/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:37:40 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 20:01:01 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(int const a, char *const b)
{
	t_token *const	output = malloc(sizeof(t_token));

	if (!output)
		return (NULL);
	output->type = a;
	output->str = b;
	output->next = NULL;
	output->prev = NULL;
	return (output);
}
