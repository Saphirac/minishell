/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:56:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/12 20:24:41 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cpy_until_quotes(char *token_str, char *cmp)
{

/*
	echo | '"'$USER'"'
	       '"' | $USER | '"'
	         ^
		   ^
*/
}

int	ft_env_cpy(char *env_value, char *tmp, char *cmp)
{
	int	i;

	i = 0;
	while (cmp[i] && cmp[i] != '$')
		i++;
	if (i == 0)
		tmp = ft_strdup(env_value);
	else
	{
		tmp = ft_strndup(cmp, i);
		if (!tmp)
			return (free(cmp), EXIT_FAILURE);
		tmp = ft_strjoin(tmp, env_value);
	}
	if (!tmp)
		return (free(cmp), EXIT_FAILURE);
	return (free(cmp), EXIT_SUCCESS);
}

int	search_env(t_env_lst *env, char *token_str, char *tmp)
{
	t_env	*tmp_env;
	char	*cmp;
	
	if (ft_cpy_until_quotes(token_str, cmp) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	tmp_env = env->head;
	while (tmp)
	{
		if (ft_env_cmp(env, cmp) == EXIT_SUCCESS)
		{
			if (ft_env_cpy(env, tmp, cmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
				return (EXIT_SUCCESS);
		}
	}
	tmp = ft_strdup(cmp);
	if (!tmp)
		return (free(cmp), EXIT_FAILURE);
	return (free(cmp), EXIT_SUCCESS);
}
