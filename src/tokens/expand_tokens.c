/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:43:53 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/22 05:29:46 by mcourtoi         ###   ########.fr       */
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

int	final_token_lst(t_token_lst *token_lst, t_env_lst *env_lst)
{
	t_token		*tmp;
	t_str_lst	str;
	int			i;

	tmp = token_lst->head;
	ft_bzero(&str, sizeof(t_str_lst));
	i = -1;
	while (tmp)
	{
		while (tmp && tmp->str[++i])
		{
			if (tmp->str[i] == '\'' || tmp->str[i] == '$' || tmp->str[i] == '"')
			{
				if (create_str_lst(tmp, &str) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				print_str_lst(&str);
				if (expand_dollars_str_lst(env_lst, &str) == EXIT_FAILURE)
					return (str_lst_clear(&str), EXIT_FAILURE);
				if (add_str_to_token(token_lst, tmp, &str) == EXIT_FAILURE)
					return (str_lst_clear(&str), EXIT_FAILURE);
				i = -1;
				tmp = tmp->next;
				str_lst_clear(&str);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (str_lst_clear(&str), EXIT_SUCCESS);
}
