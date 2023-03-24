/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:43:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/22 17:20:51 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_str_lst(t_str_lst *str)
{
	t_str	*tmp;

	tmp = str->head;
	while (tmp)
	{
		printf("str : %s\n", tmp->str);
		tmp = tmp->next;
	}
}

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
			if (expand_dollars_str_lst(env_lst, &str) == EXIT_FAILURE)
				return (str_lst_clear(&str), EXIT_FAILURE);
			print_str_lst(&str);
			if (add_str_to_token(token_lst, tmp, &str) == EXIT_FAILURE)
				return (str_lst_clear(&str), EXIT_FAILURE);
			str_lst_clear(&str);
		}
		tmp = tmp->next;
	}
	return (str_lst_clear(&str), EXIT_SUCCESS);
}
