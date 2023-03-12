/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/12 04:47:34 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*expand_single_quotes(t_token *token, char *ret)
{
	char *tmp;
	
	tmp = ft_strndup((token->str + 1), ft_strlen(token->str) - 2);
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

int	expand_double_quotes(t_shell *shell, t_token *token, char *ret)
{
	char	*tmp;
	int		i;

	i = 0;
	while (token->str[i] && token->str[i] != '$')
		i++;
	if (!token->str[i])
	{
		tmp = ft_strndup((token->str + 1), ft_strlen(token->str) - 2);
		if (!tmp)
			return (free(ret), EXIT_FAILURE);
	}
	else if (token->str[i] == '$')
		if (search_env(&shell->env, token, tmp) == EXIT_FAILURE)
			return (free(ret), EXIT_FAILURE);
	if (ret)
		ret = ft_strjoin(ret, tmp);
	else
		ret = ft_strdup(tmp);
	if (!ret)
		return (free(tmp), EXIT_FAILURE);
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_env_cmp(t_env *env, t_token *token)
{
	
}

int	search_env(t_env_lst *env, t_token *token, char *tmp)
{
	t_env	tmp;

	tmp = env->head;
	while (tmp)
	{
		
	}
	return (EXIT_SUCCESS);
}
