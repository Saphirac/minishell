/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:06:44 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/25 16:53:34 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_quotes(t_str *str)
{
	str->str = ft_strndup((str->str + 1), ft_strlen(str->str) - 2);
	if (!str->str)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Check if 1st or last char of str is a space.
 * Str cannot be null so ft_strlen(str) - 1 cannot segfault.
 * 
 * @param str 
 * @return true 
 * @return false 
 */
bool	check_spaces(char *str)
{
	return (str[0] == ' ' || str[ft_strlen(str) - 1] == ' ');
}

int	strdup_or_join(t_token *const *token, char *tmp)
{
	if (ft_strlen((*token)->str) == 0)
		(*token)->str = ft_strdup(tmp);
	else
		(*token)->str = ft_strjoin((*token)->str, tmp);
	return ((*token)->str == NULL);
}

int	add_split(t_token_lst *const token_lst, t_token **token, char **split, int i)
{
	char	*tmp_str;

	while (token && split[++i])
	{
		tmp_str = ft_strdup(split[i]);
		if (!tmp_str)
			return (EXIT_FAILURE);
		if (token_lst_add_after(token_lst, (*token),
				T_ARGUMENT, tmp_str) == EXIT_FAILURE)
			return (free(tmp_str), EXIT_FAILURE);
		free(tmp_str);
		(*token) = (*token)->next;
	}
	return (EXIT_SUCCESS);
}

int	add_split_new_token(t_token_lst *const token_lst,
	t_token **token, t_str *tmp)
{
	char	**split;

	split = ft_split(tmp->str, " \t\n");
	if (!split)
		return (EXIT_FAILURE);
	if (strdup_or_join(token, split[0]) == EXIT_FAILURE)
		return (free(split), EXIT_FAILURE);
	if (add_split(token_lst, token, split, 0) == EXIT_FAILURE)
		return (free(split), EXIT_FAILURE);
	return (free(split), EXIT_SUCCESS);
}

/* If a space is found on the first character of tmp->str, 
function creates a new token if the precedent one contain something 
if split[0] == NULL, it mean that all the tmp is spaces or tab or newline, 
in this case, it also creates a new token if token->str is full and tmp->next exists 
if split exists but token->str is empty, it will add to it even if 1st char == space
else, it will create a new token directly with the split
if last char == space it will at the end create a new token but empty and switch on it
(only if tmp->next exists)*/
int	add_spaces_new_token(t_token_lst *const token_lst, t_token **token, t_str *tmp)
{
	char	**split;

	split = ft_split(tmp->str, " \t\n");
	if (!split)
		return (EXIT_FAILURE);
	if (split[0] == NULL && tmp->next)
	{
		free(split);
		if (ft_strlen((*token)->str) != 0)
		{
			if (token_lst_add_after(token_lst, (*token), T_ARGUMENT, "") == EXIT_FAILURE)
				return (EXIT_FAILURE);
			(*token) = (*token)->next;
		}
	}
	if (tmp->str[0] == ' ')
	{
		if (ft_strlen((*token)->str) == 0)
			if (strdup_or_join(token, split[0]) == EXIT_FAILURE)
				return (free(split), EXIT_FAILURE);
	}
	else if (strdup_or_join(token, split[0]) == EXIT_FAILURE)
				return (free(split), EXIT_FAILURE);
	if (add_split(token_lst, token, split,
		(ft_strlen((*token)->str) != 0 && tmp->str[0] != ' ') * -1) == EXIT_FAILURE)
			return (free(split), EXIT_FAILURE);
	if (tmp->str[ft_strlen(tmp->str) - 1] == ' ' && tmp->next)
	{
		if (token_lst_add_after(token_lst, (*token), T_ARGUMENT, "") == EXIT_FAILURE)
			return (free(split), EXIT_FAILURE);
		(*token) = (*token)->next;
	}
	return (free(split), EXIT_SUCCESS);
}

int	do_split_on_str(t_token_lst *const token_lst, t_token **token, t_str *tmp)
{
	if (check_spaces(tmp->str) == true)
		return (add_spaces_new_token(token_lst, token, tmp));
	else
		return (add_split_new_token(token_lst, token, tmp));
}

int	add_str_to_token(t_token_lst *const token_lst, t_token **token, t_str *tmp)
{
	if (tmp->str[0] == '\'' || tmp->str[0] == '"')
	{
		if (expand_quotes(tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (strdup_or_join(token, tmp->str));
	}
	return (do_split_on_str(token_lst, token, tmp));
}

/* Parse the str_lst expanded
Get the quotes off if there is any 
if there is no quotes but there is a space, do a split
and add each part of the split to new tokens and reclassify them
do that for each node of str */

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
			if (add_str_to_token(token_lst, token, tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
