/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:43:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:11:42 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given string contains a ', a " or a $.
 * 
 * @param str to check.
 * @return true if string contain the mentionned char.
 * @return false if string doesn't contain the mentionned char.
 */
static inline bool	__need_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '$' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Attributes the token_type T_TO_SUPPR
 * to a token if it is empty and not quoted.
 * If the soon-to-be deleted token was a T_COMMAND,
 * parse the rest of the list to re-attribute
 * the T_COMMAND type to the next found T_ARGUMENT.
 * (No problem if arg is never found).
 * 
 * @param token to eventually retype.
 * @param str str_lst used to see if token needs to be retyped or not.
 */
inline static void	__need_to_delete(t_token *token, t_str_lst *str)
{
	t_token_type	tmp;

	tmp = token->type;
	if (str->size == 1 && !str->head->is_quoted && !*token->str)
	{
		token->type = T_TO_SUPPR;
		if (tmp == T_COMMAND)
		{
			while (token && token->type != T_PIPE && token->type != T_ARGUMENT)
				token = token->next;
			if (token && token->type == T_ARGUMENT)
				token->type = T_COMMAND;
		}
	}
}

/**
 * @brief Delete all the tokens with T_TO_SUPPR type from token_lst.
 * 
 * @param token_lst list we need to delete from.
 */
inline static void	__clean_final_lst(t_token_lst *token_lst)
{
	t_token	*tmp;
	t_token	*del;

	del = token_lst->head;
	while (del)
	{
		tmp = del->next;
		if (del->type == T_TO_SUPPR)
			token_lst_del_one(token_lst, del);
		del = tmp;
	}
}

/**
 * @brief After recuperation of tokens, expand $,
 * delete the quotes and retypes if necessary.
 * 
 * @param token_lst list to expand / clean.
 * @param env_lst contains every variable of the env, necessary to expand $.
 * @return EXIT_FAILURE if str_lst creation fails or a malloc fails,
 * EXIT_SUCCESS else.
 */
int	final_token_lst(t_token_lst *token_lst, t_env_lst *env_lst)
{
	t_token		*tmp;
	t_str_lst	str;

	tmp = token_lst->head;
	ft_bzero(&str, sizeof(t_str_lst));
	while (tmp)
	{
		if (__need_to_expand(tmp->str) == true)
		{
			if (create_str_lst(tmp, &str) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (expand_dollars_str_lst(env_lst, &str, tmp) == EXIT_FAILURE)
				return (str_lst_clear(&str), EXIT_FAILURE);
			if (add_str_to_tokens(token_lst, &tmp, &str) == EXIT_FAILURE)
				return (str_lst_clear(&str), EXIT_FAILURE);
			__need_to_delete(tmp, &str);
			str_lst_clear(&str);
		}
		tmp = tmp->next;
	}
	__clean_final_lst(token_lst);
	return (str_lst_clear(&str), EXIT_SUCCESS);
}
