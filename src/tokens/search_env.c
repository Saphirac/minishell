/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:56:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/29 02:33:03 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iters in the chain from a dollar to the next "stop" characters 
(non alphanumeric character and non '_') 
Check if name between that corresponds to an env value 
If true, copy the value 
else return a NULL chain */

int	append_if_exit_code(char **ret, t_str *str, t_tmp_i_start *i)
{
	char	*tmp;

	tmp = ft_hhutoa(g_exit_code);
	if (!tmp)
		return (EXIT_FAILURE);
	if (append_to_ret(ret, tmp, str, i) == EXIT_FAILURE)
		return (free(tmp), EXIT_FAILURE);
	++i->i;
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_get_dollars(t_env_lst *env, t_str *str, char **ret, t_tmp_i_start *i)
{
	t_env	*tmp_env;
	char	c;

	++i->i;
	i->start = i->i;
	while (str->str[i->i] && (ft_isalnum(str->str[i->i]) == true
			|| str->str[i->i] == '_'))
		++i->i;
	c = str->str[i->i];
	str->str[i->i] = 0;
	if (c == '?' && str->str[i->i - 1] == '$')
		return (append_if_exit_code(ret, str, i));
	tmp_env = env_lst_get_one(env, str->str + i->start);
	str->str[i->i] = c;
	if (tmp_env && append_to_ret(ret, tmp_env->value, str, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Iters trough chain until finding a dollar 
Append or copy everything before that dollar 
Then check if the name after the dollar is correct 
Append correct value if exists in the env 
Else append NULL 
Copy or append everything even the dollar if next character not correct */
int	search_env_process_one(t_env_lst *env, t_str *str,
		t_tmp_i_start *i, char **ret)
{
	i->start = i->i;
	while (str->str[i->i] && str->str[i->i] != '$')
		++i->i;
	if (str->str[i->i] == '\0')
		return (append_to_ret(ret, NULL, str, i));
	else if (str->str[i->i + 1] == '\0'
		|| (ft_isalnum(str->str[i->i + 1]) == false
			&& str->str[i->i + 1] != '_' && str->str[i->i + 1] != '?'))
	{
		++i->i;
		return (append_to_ret(ret, NULL, str, i));
	}
	else if (append_to_ret(ret, NULL, str, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ft_get_dollars(env, str, ret, i) == EXIT_FAILURE)
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
	free(str->str);
	str->str = ret;
	return (EXIT_SUCCESS);
}

/* Function parse a str_lst node and expand it via search_env
after doing that with every node copy it without the quotes
separate between two tokens on special case 
if separated, new token will need to be re-classifyied 
command token will become command + argument 
argument token will become 2 arguments 
will need to make a function to do that with every tokens*/

int	expand_dollars_str_lst(t_env_lst *env_lst,
	t_str_lst *str_lst, t_token *token)
{
	t_str	*tmp;
	int		i;

	tmp = str_lst->head;
	while (tmp)
	{
		if (tmp->str[0] != '\'' && token->type != T_DELIMITER)
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
