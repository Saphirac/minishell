/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:48:49 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/27 21:41:07 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get double op get '<<' or '>>' operators */

char	*ft_get_double_op(t_shell *shell, int *i)
{
	char	*ret;

	ret = NULL;
	if (shell->line[*i] == '<' && shell->line[*i + 1] == '<')
		ret = ft_strdup("<<");
	else if (shell->line[*i] == '>' && shell->line[*i + 1] == '>')
		ret = ft_strdup(">>");
	if (!ret)
		return (NULL);
	++*i;
	return (ret);
}

/* get_operator create a token corresponding to the operator found in the line
also create a token for the word before if it exists */

char	*ft_get_operator(t_shell *shell, int *i, int j)
{
	char	*ret;

	ret = NULL;
	if (*i > 0 && ft_is_sep(shell->line[*i - 1]))
	{
		ret = ft_strndup((shell->line + j), (*i - j));
		if (!ret)
			return (NULL);
		if (token_lst_add_back(&(shell->tokens), T_WORD, ret) == EXIT_FAILURE)
			return (NULL);
		ft_memdel(&ret);
	}
	if (shell->line[*i] == '|')
		ret = ft_strdup("|");
	else if ((shell->line[*i] == '<' && shell->line[*i + 1] == '<')
		|| (shell->line[*i] == '>' && shell->line[*i + 1] == '>'))
		ret = ft_get_double_op(shell, i);
	else if (shell->line[*i] == '<')
		ret = ft_strdup("<");
	else if (shell->line[*i] == '>')
		ret = ft_strdup(">");
	if (!ret)
		return (NULL);
	++*i;
	return (ret);
}
