/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:50:26 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:12:56 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_is_null(t_token_lst *const token_lst,
		t_token **const token, t_str const *const tmp)
{
	if (*(*token)->str || (tmp->prev && tmp->prev->is_quoted == true))
	{
		if (tmp->next)
		{
			if (!token_lst_add_after(token_lst, (*token), T_ARGUMENT, ""))
				return (EXIT_FAILURE);
			(*token) = (*token)->next;
		}
	}
	return (EXIT_SUCCESS);
}

int	add_spaces(t_token_lst *const token_lst, t_token **token,
		t_str *tmp, char **split)
{
	if (*(*token)->str || (tmp->prev && tmp->prev->is_quoted == true))
	{
		if (add_split(token_lst, token, split, -1))
			return (free(split), EXIT_FAILURE);
	}
	else if (strdup_or_join(token, split[0])
		|| add_split(token_lst, token, split, 0))
		return (free(split), EXIT_FAILURE);
	if (is_white_spaces(tmp->str[ft_strlen(tmp->str) - 1]))
	{
		if (tmp->next && *(*token)->str)
		{
			if (!token_lst_add_after(token_lst, (*token), T_ARGUMENT, ""))
				return (free(split), EXIT_FAILURE);
			(*token) = (*token)->next;
		}
	}
	return (free(split), EXIT_SUCCESS);
}

/**
 * @brief If token being expanded is unquoted and contains space,
 * separates between as many tokens needed.
 * Uses t_token_lst_add_after() to do that.
 * 
 * @param token_lst list containing all t_token.
 * @param token token being expanded.
 * @param tmp t_str containing the part of token.
 * @return EXIT_FAILURE or EXIT_SUCCESS.
 */
int	add_spaces_new_token(t_token_lst *const token_lst,
		t_token **token, t_str *tmp)
{
	char	**split;

	split = ft_split(tmp->str, " \t\n");
	if (!split)
		return (EXIT_FAILURE);
	if (split[0] == NULL)
		return (free(split), split_is_null(token_lst, token, tmp));
	if (is_white_spaces(tmp->str[0]) == true)
		return (add_spaces(token_lst, token, tmp, split));
	if (strdup_or_join(token, split[0])
		|| add_split(token_lst, token, split, 0))
		return (free(split), EXIT_FAILURE);
	if (is_white_spaces(tmp->str[ft_strlen(tmp->str) - 1]))
	{
		if (tmp->next && ft_strlen((*token)->str))
		{
			if (!token_lst_add_after(token_lst, (*token), T_ARGUMENT, ""))
				return (free(split), EXIT_FAILURE);
			(*token) = (*token)->next;
		}
	}
	return (free(split), EXIT_SUCCESS);
}
