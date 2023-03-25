/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:56:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/25 06:29:50 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_tmp_i_start
{
	int	i;
	int	start;
}	t_tmp_i_start;

int	append_to_ret(char **ret, char *tmp, t_str *str, t_tmp_i_start *i)
{
	char	*tmp_2;

	if (i->i == 0 && str->str[i->i + 1] == '\0')
		*ret = ft_strdup(str->str);
	else if (i->i == 0)
		*ret = ft_strdup("");
	else if (!*ret && !tmp)
		*ret = ft_strndup(str->str + i->start, i->i - i->start);
	else if (!*ret)
		*ret = ft_strdup(tmp);
	else if (!tmp)
	{
		tmp_2 = ft_strndup(str->str + i->start, i->i - i->start);
		if (!tmp_2)
			return (ft_memdel(ret), EXIT_FAILURE);
		*ret = ft_strjoin(*ret, tmp_2);
		if (!*ret)
			return (free(tmp_2), EXIT_FAILURE);
		return (free(tmp_2), EXIT_SUCCESS);
	}
	else
		*ret = ft_strjoin(*ret, tmp);
	if (!*ret)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Iters in the chain from a dollar to the next "stop" characters 
(non alphanumeric character and non '_') 
Check if name between that corresponds to an env value 
If true, copy the value 
else return a NULL chain */

int	ft_get_dollars(t_env_lst *env, t_str *str, char **ret, t_tmp_i_start *i)
{
	t_env	*tmp_env;
	char	*name;

	++i->i;
	i->start = i->i;
	while (str->str[i->i] && (ft_isalnum(str->str[i->i]) == true
		|| str->str[i->i] == '_'))
		++i->i;
	name = ft_strndup(str->str + i->start, i->i - i->start);
	if (!name)
		return (free(*ret), EXIT_FAILURE);
	tmp_env = env_lst_get_one(env, name);
	free(name);
	if (tmp_env)
	{
		name = ft_strdup(tmp_env->value);
		if (!name)
			return (ft_memdel(ret), EXIT_FAILURE);
		if (append_to_ret(ret, name, str, i) == EXIT_FAILURE)
			return (free(name), ft_memdel(ret), EXIT_FAILURE);
		free(name);
	}
	return (EXIT_SUCCESS);
}

/* Iters trough chain until finding a dollar 
Append or copy everything before that dollar 
Then check if the name after the dollar is correct 
Append correct value if exists in the env 
Else append NULL 
Copy or append everything even the dollar if next character not correct */

// TODO : handle special case "?"
int	search_env_process_one(t_env_lst *env, t_str *str, t_tmp_i_start *i, char **ret)
{
	i->start = i->i;
	while (str->str[i->i] && str->str[i->i] != '$')
		++i->i;
	if (str->str[i->i] == '\0')
		return (append_to_ret(ret, NULL, str, i));
	else if (str->str[i->i + 1] == '\0' ||
			(ft_isalnum(str->str[i->i + 1]) == false && str->str[i->i + 1] != '_'))
	{
		++i->i;
		return (append_to_ret(ret, NULL, str, i));
	}
	else if (append_to_ret(ret, NULL, str, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	else
		if (ft_get_dollars(env, str, ret, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	search_env(t_env_lst *env, t_str *str)
{
	char			*ret;
	t_tmp_i_start	i;

	i.i = 0;
	ret = NULL;
	while (str->str[i.i])
		if (search_env_process_one(env, str, &i, &ret) == EXIT_FAILURE)
			return (ft_memdel(&ret), EXIT_FAILURE);
	if (ret)
	{
		printf("ret : %s\n", ret);
		str->str = ft_strdup(ret);
		if (!str->str)
			return (ft_memdel(&ret), EXIT_FAILURE);
	}
	return (ft_memdel(&ret), EXIT_SUCCESS);
}

/* Function parse a str_lst node and expand it via search_env
after doing that with every node copy it without the quotes
separate between two tokens on special case 
if separated, new token will need to be re-classifyied 
command token will become command + argument 
argument token will become 2 arguments 
will need to make a function to do that with every tokens*/

int	expand_dollars_str_lst(t_env_lst *env_lst, t_str_lst *str_lst)
{
	t_str	*tmp;
	int		i;

	tmp = str_lst->head;
	while (tmp)
	{
		if (tmp->str[0] != '\'')
		{
			i = 0;
			while (tmp->str[i] && tmp->str[i] != '$')
				i++;
			if (tmp->str[i] == '$')
				if (search_env(env_lst, tmp) == EXIT_FAILURE)
					return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
