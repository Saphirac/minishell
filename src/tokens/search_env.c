/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:56:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/19 07:37:48 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_tmp_i_start
{
	int	i;
	int	start;
}	t_tmp_i_start;

int	append_to_ret(char *ret, char *tmp, t_tmp_i_start *i)
{
	if (i->i == 0)
		ret = ft_strndup();
	if (!ret && !tmp)
		ret = ft_strndup(str->str + i->start, i->i - 1);
	else if (!ret)
		ret = ft_strdup(tmp);
	else if (!tmp)
	{
		tmp = ft_strndup(str->str + i->start, i->i - i->start);
		if (!tmp)
			return (ft_memdel(&ret), EXIT_FAILURE);
		ret = ft_strjoin(ret, tmp);
	}
	else
		ret = ft_strjoin(ret, tmp);
	if (!ret)
		return (ft_memdel(&tmp), EXIT_FAILURE);
	return (ft_memdel(&tmp), EXIT_SUCCESS);
}

/* Iters in the chain from a dollar to the next "stop" characters 
(non alphanumeric character and non '_') 
Check if name between that corresponds to an env value 
If true, copy the value 
else return a NULL chain */

int	ft_get_dollars(t_env_lst *env, t_str *str, char *ret, t_tmp_i_start *i)
{
	t_env	tmp_env;
	char	*name;

	i->start = i;
	while (str->str[i->i] && ft_alnum(str->str[i->i]) == true
		|| str->str[i->i] == '_')
		++(i->i);
	name = ft_strndup(str->str + i->i + 1, i->i - i->start);
	if (!name)
		return (free(ret), EXIT_FAILURE);
	tmp_env = env_lst_get_one(env, name);
	if (tmp_env)
	{
		name = ft_strdup(tmp_env->value);
		if (!name)
			return (ft_memdel(&ret), EXIT_FAILURE);
		if (append_to_ret(ret, name, i) == EXIT_FAILURE)
			return (ft_memdel(&ret), EXIT_FAILURE);
	}
	return (ft_memdel(&name), EXIT_SUCCESS);
}

/* Iters trough chain until finding a dollar 
Append or copy everything before that dollar 
Then check if the name after the dollar is correct 
Append correct value if exists in the env 
Else append NULL 
Copy or append everything even the dollar if next character not correct */

int	search_env_process_one(t_env_lst *env, t_str *str, t_tmp_i_start *i)
{
	i->start = i->i;
	while (str->str[i->i] && str->str[i->i] != '$')
		++i->i;
	if (append_to_ret(ret, NULL, &i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (str->str[i->i] == '\0')
		return (EXIT_SUCCESS);
	++i->i;
	if (str->str[i->i] == '\0')
		return (append_to_ret(ret, NULL, &i));
	if (ft_isalnum(str->str[i->i]) == false && str->str[i->i] != '_')
		++i->i;
	else
		if (ft_get_dollars(env, str, ret, &i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
}

int	search_env(t_env_lst *env, t_str *str)
{
	char			*ret;
	t_tmp_i_start	i;

	i.i = 0;
	ret = NULL;
	while (str->str[i.i])
		search_env_process_one(env, str, &i);
	str->str = ft_strdup(ret);
	if (!str->str)
		return (EXIT_FAILURE);
	return (ft_memdel(&ret), (EXIT_SUCCESS));
}
