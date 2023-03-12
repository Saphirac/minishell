/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/12 20:03:07 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*expand_single_quotes(char *token_str, char *ret)
{
	char 	*tmp;

	tmp = ft_strndup((token_str + 1), ft_strlen(token_str) - 2);
	if (!tmp)
		return (free(ret), EXIT_FAILURE);
	if (ret)
		ret = ft_strjoin(ret, tmp);
	else
		ret = ft_strdup(tmp);
	if (!ret)
		return (free(tmp), EXIT_FAILURE);
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_expand_double_quotes(t_shell *shell, char *token_str, char *ret)
{
	char	*tmp;
	int		i;

	i = 0;
	if (search_env_double(&shell->env, token_str, tmp) == EXIT_FAILURE)
			return (free(ret), EXIT_FAILURE);
	if (ret)
		ret = ft_strjoin(ret, tmp);
	else
		ret = ft_strdup(tmp);
	if (!ret)
		return (free(tmp), EXIT_FAILURE);
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_expand(t_shell *shell, t_token *token)
{
	char	*ret;
	int		i;

	i = 0;
	while (token->str[i] && token->str[i] )
}
