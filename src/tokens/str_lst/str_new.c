/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:37:40 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/29 02:29:48 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	*str_new(char *const str, bool is_quoted)
{
	t_str *const	output = malloc(sizeof(t_str));

	if (!output)
		return (NULL);
	output->str = ft_strdup(str);
	if (!output->str)
		return (free(output), NULL);
	output->is_quoted = is_quoted;
	output->next = NULL;
	output->prev = NULL;
	return (output);
}
