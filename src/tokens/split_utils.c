/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:48:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 21:19:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white_spaces(char const c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	check_white_spaces(char const *const str)
{
	return (is_white_spaces(str[0])
		|| is_white_spaces(str[ft_strlen(str) - 1]));
}

int	strdup_or_join(t_token *const *const token, char const *const tmp)
{
	char	*tmp_ptr;

	if (ft_strlen((*token)->str) == 0)
	{
		free((*token)->str);
		(*token)->str = ft_strdup(tmp);
	}
	else
	{
		tmp_ptr = (*token)->str;
		(*token)->str = ft_strjoin((*token)->str, tmp);
		free(tmp_ptr);
	}
	return ((*token)->str == NULL);
}

int	add_split(t_token_lst *const token_lst,
			t_token **const token, char **split, int i)
{
	char	*tmp_str;

	while (token && split[++i])
	{
		tmp_str = ft_strdup(split[i]);
		if (!tmp_str)
			return (EXIT_FAILURE);
		if (token_lst_add_after(token_lst, (*token), T_ARGUMENT, tmp_str)
			== NULL)
			return (free(tmp_str), EXIT_FAILURE);
		free(tmp_str);
		(*token) = (*token)->next;
	}
	return (EXIT_SUCCESS);
}
