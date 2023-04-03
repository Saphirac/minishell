/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:06:44 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:15:19 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	__expand_quotes(t_str *str)
{
	size_t	len_str;

	len_str = ft_strlen(str->str);
	ft_memcpy(str->str, str->str + 1, len_str - 2);
	str->str[len_str - 2] = '\0';
}

inline static int	__add_split_new_token(t_token_lst *const token_lst,
	t_token **token, t_str *tmp)
{
	char	**split;

	split = ft_split(tmp->str, " \t\n");
	if (!split)
		return (EXIT_FAILURE);
	if (split[0] == NULL)
		return (free(split), EXIT_SUCCESS);
	if (strdup_or_join(token, split[0]) == EXIT_FAILURE)
		return (free(split), EXIT_FAILURE);
	if (add_split(token_lst, token, split, 0) == EXIT_FAILURE)
		return (free(split), EXIT_FAILURE);
	return (free(split), EXIT_SUCCESS);
}

inline static int	__do_split_on_str(
	t_token_lst *const token_lst,
	t_token **token,
	t_str *tmp)
{
	if (check_white_spaces(tmp->str) == true)
		return (add_spaces_new_token(token_lst, token, tmp));
	return (__add_split_new_token(token_lst, token, tmp));
}

inline static int	__add_str_to_token(
	t_token_lst *const token_lst,
	t_token **token, t_str *tmp)
{
	if (tmp->is_quoted == true)
	{
		__expand_quotes(tmp);
		if ((*token)->type == T_DELIMITER)
			((*token)->type = T_DELIMITER_QUOTED);
		return (strdup_or_join(token, tmp->str));
	}
	if ((*token)->type != T_ARGUMENT && (*token)->type != T_COMMAND)
		return (strdup_or_join(token, tmp->str));
	return (__do_split_on_str(token_lst, token, tmp));
}

/**
 * @brief Parse the str_lst expanded, get the quotes off if there is any.
 * If there is no quotes but there is a space,
 * do a split and add each part of the split
 * to new tokens and reclassify them.
 * 
 * @param token_lst list containing all t_token.
 * @param token being expanded actually.
 * @param str struct containing each part of token.
 * @return EXIT_FAILURE or EXIT_SUCCESS.
 */
int	add_str_to_tokens(t_token_lst *const token_lst, t_token **token,
	t_str_lst *const str)
{
	t_str	*tmp;

	tmp = str->head;
	free((*token)->str);
	(*token)->str = ft_strdup("");
	if (!(*token)->str)
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (ft_strlen(tmp->str) != 0)
			if (__add_str_to_token(token_lst, token, tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
