/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:43:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/29 17:54:38 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			str_lst_clear(&str);
		}
		tmp = tmp->next;
	}
	__clean_final_lst(token_lst);
	return (str_lst_clear(&str), EXIT_SUCCESS);
}
