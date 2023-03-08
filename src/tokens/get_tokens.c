/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:35:35 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/09 03:42:32 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* All functions ft_add are there to protect
from alloc errors and fit the norm */

int	ft_add_operator(t_shell *shell, int *i, int j)
{
	tmp = ft_get_operator(shell, &i, j);
	if (!tmp)
		return (EXIT_FAILURE);
	if (token_lst_add_back(shell->tokens, T_OPERATOR,
			tmp == EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_add_word(t_shell *shell, int i, int j)
{
	tmp = ft_strndup((shell->line + j), (i - j));
	if (!tmp)
		return (EXIT_FAILURE);
	if (token_lst_add_back(shell->tokens, T_WORD, tmp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* ft_quotes iters i until encounter with the second quote. */

int	ft_quotes(t_shell *shell, int *i)
{
	if (shell->line[*i] == '"')
		while (shell->line[*i], shell->line[*i] != '"')
			*++i;
	if (shell->line[*i] == '\'')
		while (shell->line[*i], shell->line[*i] != '\'')
			*++i;
	if (!shell->line[*i])
	{
		printf("Syntax error.\n");
		return (EXIT_FAILURE);
	}
	*++i;
	return (EXIT_SUCCESS);
}

/* Function browse line until it gets to a quote,
an operator or a space. 
It then calls the right function to get the corresponding tokens
and then continue to browse */

int	tokens_get(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (shell->line[i])
	{
		while (shell->line[i] && shell->line[i] != ' ')
			i++;
		j = i;
		while (ft_is_sep(shell->line[i]))
			i++;
		if (!shell->line[i] || shell->line[i] == ' ')
			if (ft_add_word(shell, &i, j) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		else if (ft_is_op(shell->line[i]) == 0)
			if (ft_add_operator(shell, &i, j) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		else if (shell->line[i] == '"' || shell->line[i] == '\'')
			ft_quotes(shell, &i);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
