/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:36:10 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/13 00:10:06 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int	ft_cpy_without_quotes(char *token_str, char *cmp)
{
	int		i;

	i = 1;
	while (token_str[i] && token_str[i] != '"')
		i++;
	cmp = ft_strndup(token_str + 1, i);
	if (!cmp)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	search_env_double(t_env_lst *env, char *token_str, char *tmp)
{
	t_env	*tmp_env;
	char	*cmp;
	char	*name;
	int		i;

	if (ft_cpy_without_quotes(token_str, cmp) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	i = 0;
	while (cmp[i] && cmp[i] != '$')
		i++;
	if (cmp[i] == '$')
	{
		name = ft_strndup(cmp + i + 1, ft_strlen(cmp) - (i + 1));
		if (!name)
			return (free(cmp), free(tmp), EXIT_FAILURE);
		if (ft_check_dollars(name) == EXIT_SUCCESS)
		{
			tmp_env = env_lst_get_one(env, name);
			if (tmp_env)
			{	
				if (ft_env_cpy(tmp_env->value, tmp, cmp) == EXIT_FAILURE)
					return (free(cmp), free(name), EXIT_FAILURE);
				else
					return (free(cmp), free(name), EXIT_SUCCESS);
			}
		}
		else
		{
			tmp = ft_strdup(cmp);
			return (free(cmp), free(name), EXIT_SUCCESS);
		}
	}
	if (i != 0)
		tmp = ft_strndup(cmp, i);
	if (!tmp)
		return (free(cmp), free(name), EXIT_FAILURE);
	if (i = 0)
		tmp = NULL;
	return (free(cmp), free(name), EXIT_SUCCESS);
}
