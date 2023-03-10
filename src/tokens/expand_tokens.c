/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/10 20:06:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

#include "minishell.h"

char	*expand_single_quotes(char *token)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (ft_strlen(token) - 2 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (token[++i])
		ret[i - 1] = token[i];
	ret[i - 1] = '\0';
	return (ret);
}

char	*expand_double_quotes(t_shell *shell, char *token)
{
	char	*ret;
	int		i;
	char	*tmp;

	i = 1;
	while (token[i] && token[i] != '$')
		i++;
	if (token[i] == '$')
	{
		tmp = search_env(shell->env, token);
		if (!tmp)
			return (NULL);
		ret = expand_dollar(token, tmp);
		if (!ret)
			return (NULL);
		return (ret);
	}
	return (NULL);
}

static int	compare_env_token(char *env, char *token)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=' && token[i] == '\0')
			return (i);
		if (env[i] != token[i])
			return (-1);
		i++;
	}
	return (-2);
}

char	*search_env(char **env, char *token)
{
	int		i;
	int		tmp;
	char	*ret;
	int		j;

	j = 0;
	while (token[j] && token[j] != '$')
		j++;
	i = -1;
	tmp = -1;
	while (env[++i] && tmp < 0)
		tmp = compare_env_token(env[i], (token + j + 1));
	if (env[i - 1] && tmp > 0)
	{
		ret = ft_strdup(env[i - 1] + (tmp + 1));
		if (!ret)
			return (NULL);
		return (ret);
	}
	return (NULL);
}

char	*expand_dollar(char *token, char *tmp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	ret = malloc(sizeof(char) * (i + ft_strlen(tmp) + 1));
	i = -1;
	while (token[++i] && token[i] != '$')
		ret[i] = token[i];
	j = -1;
	while (tmp[++j])
		ret[i++] = tmp[j];
	ret[i] = '\0';
	return (ret);
}

*/
