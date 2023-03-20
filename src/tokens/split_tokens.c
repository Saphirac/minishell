/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:06:44 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/20 04:12:50 by mcourtoi         ###   ########.fr       */
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

int	add_split_new_token(t_token_lst *const token_lst,
	t_token *const token, char **split)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (token && split[++i])
	{
		tmp_str = ft_strdup(split[i]);
		if (!tmp_str)
			return (EXIT_FAILURE);
		if (token_lst_add_after(token_lst, token, T_ARGUMENT, tmp_str) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(tmp_str);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	do_split_on_str_head(t_token_lst *const token_lst, t_token *const token,
	t_str_lst *const str, t_str *tmp)
{
	char	*split;

	split = ft_split(tmp->str, ' ');
	if (!split)
		return (EXIT_FAILURE);
	if (split == NULL)
		token->str = NULL;
	else
	{
		token->str = ft_strdup(split[0]);
		if (!token->str)
			return (free_tab(split), EXIT_FAILURE);
		if (add_split_new_token(token_lst, token, split) == EXIT_FAILURE)
			return (free_tab(split), EXIT_FAILURE);
	}
	return (free_tab(split), EXIT_SUCCESS);
}

int	do_split_on_str_other(t_token_lst *const token_lst, t_token *const token,
	t_str_lst *const str, t_str *tmp)
{
	char	*split;

	split = ft_split(tmp->str, ' ');
	if (!split)
		return (EXIT_FAILURE);
	if (split == NULL)
		return (free_tab(split), EXIT_SUCCESS);
	else
	{
		token->str = ft_strjoin(token->str, split[0]);
		if (!token->str)
			return (free_tab(split), EXIT_FAILURE);
		if (add_split_new_token(token_lst, token, split) == EXIT_FAILURE)
			return (free_tab(split), EXIT_FAILURE);
	}
	return (free_tab(split), EXIT_SUCCESS);
}

int	add_str_head_to_token(t_token_lst *const token_lst, t_token *const token,
	t_str_lst *const str, t_str *tmp)
{
	if (tmp->str[0] == '\'' || tmp->str[0] == '"')
	{
		if (expand_quotes(tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		token->str = ft_strdup(tmp->str);
		if (!token->str)
			return (free(tmp->str), EXIT_FAILURE);
		free(tmp->str);
	}
	else
		return (do_split_on_str_head(token_lst, token, str, tmp));
	return (EXIT_SUCCESS);
}

int	add_str_other_to_token(t_token_lst *const token_lst, t_token *const token,
	t_str_lst *const str, t_str *tmp)
{
	if (tmp->str[0] == '\'' || tmp->str[0] == '"')
	{
		if (expand_quotes(tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		token->str = ft_strjoin(token->str, tmp->str);
		if (!token->str)
			return (free(tmp->str), EXIT_FAILURE);
		free(tmp->str);
	}
	else
		return (do_split_on_str_other(token_lst, token, str, tmp));
	return (EXIT_SUCCESS);
}

/* Parse the str_lst expanded
Get the quotes off if there is any 
if there is no quotes but there is a space, do a split
and add each part of the split to new tokens and reclassify them
do that for each node of str */

int	add_str_to_token(t_token_lst *const token_lst, t_token *const token,
	t_str_lst *const str)
{
	t_str	*tmp;

	tmp = str->head;
	if (add_str_head_to_token(token_lst, token, str, tmp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (tmp)
	{
		tmp = tmp->next;
		if (add_str_other_to_token(token_lst, token, str, tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
}

/* Need to create function that call str_lst then free it. */