/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:56:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:14:05 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief If $? is encountered,
 * remplaces it with g_exit_code value instead of an env_lst variable.
 * 
 * @param ret string we ft_strjoin() / ft_strdup() to.
 * @param str string in search for $ and expand it.
 * @param i struct containing start and i for ft_strndup().
 * @return EXIT_FAILURE or EXIT_SUCCESS.
 */
inline static int	__append_if_exit_code(
	char **ret,
	char *str,
	t_tmp_i_start *i)
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

/**
 * @brief Iters in the chain from a dollar to the next "stop" characters 
 * (non alphanumeric character and non '_').
 * Check if name between that corresponds to an env value 
 * If true, copy the value else return a NULL chain and appends it.
 * 
 * @param env env_lst containing all env variables to remplace $ with.
 * @param str string we search for $ in.
 * @param ret string we ft_strjoin() / ft_strdup() in append to ret.
 * @param i struct containing start and end for ft_strndup().
 * @return EXIT_FAILURE or EXIT_SUCCESS.
 */
inline static int	__ft_get_dollars(
	t_env_lst *env,
	char *str,
	char **ret,
	t_tmp_i_start *i)
{
	t_env	*tmp_env;
	char	c;

	++i->i;
	i->start = i->i;
	while (str[i->i] && (ft_isalnum(str[i->i]) == true
			|| str[i->i] == '_'))
		++i->i;
	c = str[i->i];
	str[i->i] = 0;
	if (c == '?' && str[i->i - 1] == '$')
		return (__append_if_exit_code(ret, str, i));
	tmp_env = env_lst_get_one(env, str + i->start);
	str[i->i] = c;
	if (tmp_env && append_to_ret(ret, tmp_env->value, str, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

inline static int	__search_env_process_one(t_env_lst *env, char *str,
		t_tmp_i_start *i, char **ret)
{
	i->start = i->i;
	while (str[i->i] && str[i->i] != '$')
		++i->i;
	if (str[i->i] == '\0')
		return (append_to_ret(ret, NULL, str, i));
	else if (str[i->i + 1] == '\0'
		|| (ft_isalnum(str[i->i + 1]) == false
			&& str[i->i + 1] != '_' && str[i->i + 1] != '?'))
	{
		++i->i;
		return (append_to_ret(ret, NULL, str, i));
	}
	else if (append_to_ret(ret, NULL, str, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (__ft_get_dollars(env, str, ret, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Iters trough chain until finding a dollar.
 * Append or copy everything before that dollar.
 * Then check if the name after the dollar is correct : 
 * Append correct value if exists in the env else append NULL 
 * Copy or append everything even the dollar if next character not correct.
 * 
 * @details use search_env_process_one for the norm.
 * 
 * @param env list containing all variable to remplace $.
 * @param str string we parse to find the $ to remplace.
 * @param i struct containing iterator i to parse str,
 * and start to ft_strndup() correctly.
 * @param ret string we copy or append to get the final str result.
 * @return EXIT_FAILURE or EXIT_SUCCESS.
 */
int	search_env(t_env_lst *env, char **str)
{
	char			*ret;
	t_tmp_i_start	i;

	i.i = 0;
	ret = NULL;
	while ((*str)[i.i])
		if (__search_env_process_one(env, *str, &i, &ret) == EXIT_FAILURE)
			return (ft_memdel(&ret), EXIT_FAILURE);
	free(*str);
	*str = ret;
	return (EXIT_SUCCESS);
}

/**
 * @brief Function parse a str_lst node and expand it via search_env.
 * Copies node without the quotes.
 * Separate between two tokens if space in an unquoted str_lst node.
 * if separated, new token will need automatically be classifyed as T_ARGUMENT.
 * 
 * @param env_lst list containing the env variables.
 * @param str_lst list with each part to expand.
 * @param token node being expanded.
 * @return EXIT_FAILURE or EXIT_SUCCESS. 
 */

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
				if (search_env(env_lst, &tmp->str) == EXIT_FAILURE)
					return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
