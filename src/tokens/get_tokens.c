/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:35:35 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/09 20:53:46 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* All functions ft_add are there to protect
from alloc errors and fit the norm */

int ft_add_operator(t_shell *shell, int *i, int *j)
{
	char *tmp;

	tmp = ft_get_operator(shell, i, *j);
	if (!tmp)
		return (EXIT_FAILURE);
	if (!ft_strlen(tmp))
		return (EXIT_SUCCESS);
	if (token_lst_add_back(&(shell->tokens), T_OPERATOR,
						   tmp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*j = -1;
	return (EXIT_SUCCESS);
}

int ft_add_word(t_shell *shell, int *i, int *j)
{
	char *tmp;

	tmp = ft_strndup((shell->line + *j), (*i - *j));
	if (!tmp)
		return (EXIT_FAILURE);
	if (!ft_strlen(tmp))
		return (EXIT_SUCCESS);
	if (token_lst_add_back(&(shell->tokens), T_WORD, tmp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (shell->line[*i] == ' ')
		++*i;
	*j = -1;
	return (EXIT_SUCCESS);
}

/* ft_quotes iters i until encounter with the second quote.
return (2) : exit syntax. */ 

int ft_add_quotes(t_shell *shell, int *i, int *j)
{
	char	type;

	type = shell->line[*i];
	(*i)++;
	while (shell->line[*i] && shell->line[*i] != type)
		++*i;
	if (shell->line[*i] != type)
		return (printf("Syntax error.\n"), 2);
	++*i;
	if (shell->line[*i] == '\0' || shell->line[*i] == ' '
		|| ft_is_op(shell->line[*i]) == 0)
		if (ft_add_word(shell, i, j) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int use_add_tokens_functions(t_shell *shell, int *i, int *j)
{
	if (!shell->line[*i] || shell->line[*i] == ' ')
		return (ft_add_word(shell, i, j));
	else if (ft_is_op(shell->line[*i]) == 0)
		return (ft_add_operator(shell, i, j));
	else if (shell->line[*i] == '"' || shell->line[*i] == '\'')
		return (ft_add_quotes(shell, i, j));
	return (EXIT_SUCCESS);
}

/* Function browse line until it gets to a quote,
an operator or a space.
It then calls the right function to get the corresponding tokens
and then continue to browse */

int tokens_get(t_shell *shell)
{
	int i;
	int j;
	int exit_code;

	i = 0;
	j = -1;
	while (shell->line[i])
	{
		while (shell->line[i] && shell->line[i] == ' ')
			i++;
		if (j == -1)
			j = i;
		while (ft_is_sep(shell->line[i]))
			i++;
		exit_code = use_add_tokens_functions(shell, &i, &j);
		if (exit_code != EXIT_SUCCESS)
			return (exit_code);
	}
	return (EXIT_SUCCESS);
}

// void	ft_scan_line(char *str)
// {
// 	t_list	*tokens;
// 	size_t	word_len;
// 	int		in_quote;

// 	in_quote = 0;
// 	while (*str)
// 	{
// 		while (*str && (*str == ' '))
// 			str++;
// 		word_len = ft_is_word(str);
// 		if (word_len)
// 		{
// 			ft_add_token(token, str);
// 			str += word_len;
// 		}
// 		str++;
// 	}
// }
