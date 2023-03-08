/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:28:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/02/28 05:05:45 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cp_token(char *tokens, char *str, int i, int j)
{
	int	k;

	k = 0;
	tokens = malloc(sizeof(char) * ((j - i) + 1));
	if (!tokens)
		return (NULL);
	while (i < j && str[i])
		tokens[k++] = str[i++];
	tokens[k] = '\0';
	return (tokens);
}

int	sub_tokens(t_shell *shell, int i, int j, int k)
{
	if (!shell->line[j] || shell->line[j] == ' ')
	{
		shell->tokens[k] = cp_token(shell->tokens[k], shell->line, i, j);
		if (!shell->tokens[k])
			return (-1);
		return (k + 1);
	}
	if (count_quotes(shell->line, j) > 0)
	{
		j += count_quotes(shell->line, j);
		shell->tokens[k] = cp_token(shell->tokens[k], shell->line, i, j);
		if (!shell->tokens[k])
			return (-3);
		k++;
	}
	return (k);
}

char	**tokens_tab(t_shell *shell, int i)
{
	int		j;
	int		k;

	k = 0;
	shell->tokens = malloc(sizeof(char *) * (count_tokens(shell->line) + 1));
	if (!shell->tokens)
		return (NULL);
	while (shell->line[i])
	{
		while (shell->line[i] && shell->line[i] == ' ')
			i++;
		if (!shell->line[i])
			return (shell->tokens);
		j = i;
		while (shell->line[j] != ' ' && shell->line[j] != '"'
			&& shell->line[j] != '\'' && shell->line[j])
			j++;
		k = sub_tokens(shell, i, j, k);
		if (k < 0)
			return (NULL);
		i = (j + count_quotes(shell->line, j));
	}
	shell->tokens[count_tokens(shell->line)] = NULL;
	return (shell->tokens);
}
