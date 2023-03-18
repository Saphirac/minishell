/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/19 19:38:55 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cpy_normal(t_token *token, t_str_lst *str_lst, int i, int j)
{
	char	*tmp;

	tmp = ft_strndup(token->str + j, (i - j));
	if (!tmp)
		return (str_lst_clear(str_lst), EXIT_FAILURE);
	if (str_lst_add_back(str_lst, tmp) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_cpy_quotes(t_token *token, t_str_lst *str_lst, int *i, int j)
{
	char	*tmp;
	char	c;

	c = token->str[*i];
	++*i;
	while (token->str[*i] && token->str[*i] != c)
		++*i;
	tmp = ft_strndup(token->str + j, (*i - j));
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
		if (token->str[i] == '\0' && j == 0)
			return (EXIT_SUCCESS);
		else if ((token->str[j] != '"' && token->str[j] != '\''))
		{
			if (ft_cpy_normal(token, str_lst, i, j) == EXIT_FAILURE)
				return (str_lst_clear(str_lst), EXIT_FAILURE);
		}
		else
			if (ft_cpy_quotes(token, str_lst, &i, j) == EXIT_FAILURE)
				return (str_lst_clear(str_lst), EXIT_FAILURE);
		i++;
		j = i;
	}
	return (EXIT_SUCCESS);
}

/* Function parse a str_lst node and expand it via search_env
after doing that with every node copy it without the quotes
separate between two tokens on special case 
if separated, new token will need to be re-classifyied 
command token will become command + argument 
argument token will become 2 arguments 
will need to make a function to do that with every tokens*/

int	expand_dollars_str_lst(t_env_lst *env_lst, t_token *token,
	t_str_lst *str_lst)
{
	t_str	*tmp;
	int		i;

	i = 0;
	tmp = str_lst->head;
	while (tmp)
	{
		while (tmp->str[i] && tmp->str[i] != '$')
			i++;
		if (tmp->str[i] == '$')
			if (search_env(env_lst, tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
