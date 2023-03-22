/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_str_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/22 04:45:03 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cpy_normal(t_token *token, t_str_lst *str_lst, int i, int *j)
{
	char	*tmp;

	tmp = ft_strndup(token->str + *j, (i - *j));
	if (!tmp)
		return (str_lst_clear(str_lst), EXIT_FAILURE);
	if (str_lst_add_back(str_lst, tmp) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	*j = i;
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_cpy_quotes(t_token *token, t_str_lst *str_lst, int *i, int *j)
{
	char	*tmp;
	char	c;

	c = token->str[*i];
	++*i;
	while (token->str[*i] && token->str[*i] != c)
		++*i;
	tmp = ft_strndup(token->str + *j, (*i - *j + 1));
	++*i;
	if (!tmp)
		return (str_lst_clear(str_lst), EXIT_FAILURE);
	if (str_lst_add_back(str_lst, tmp) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	return (free(tmp), EXIT_SUCCESS);
}

int	create_str_lst(t_token *token, t_str_lst *str_lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (token->str[i])
	{
		while (token->str[i] && token->str[i] != '"' && token->str[i] != '\'')
			i++;
		if ((token->str[j] != '"' && token->str[j] != '\''))
		{
			if (ft_cpy_normal(token, str_lst, i, &j) == EXIT_FAILURE)
				return (str_lst_clear(str_lst), EXIT_FAILURE);
		}
		if (token->str[i] == '"' || token->str[i] == '\'')
			if (ft_cpy_quotes(token, str_lst, &i, &j) == EXIT_FAILURE)
				return (str_lst_clear(str_lst), EXIT_FAILURE);
		j = i;
	}
	return (EXIT_SUCCESS);
}
