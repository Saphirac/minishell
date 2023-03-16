/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:04:44 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/22 03:42:47 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_opt	t_opt;

enum	e_opt
{
	NONE_YET,
};

struct	s_opt
{
	char const *const	str;
	uint8_t const		bit;
};

static t_opt const		g_opt[] = {
{0},
};

/**
 * @brief 	Try to match an encountered option with the supported options.
 * 
 * @param	str The encountered option to match.
 * 
 * @return	The index of the matched option in the array if any,
 * 			or the index of the null element otherwise.
 */
inline static unsigned int	__match_opt(char const *const str)
{
	unsigned int	i;

	i = 0U;
	while (g_opt[i].str)
	{
		if (!ft_strcmp(str, g_opt[i].str))
			return (i);
		++i;
	}
	return (i);
}

/**
 * @brief	Parse the first given tokens and save the encountered options
 * 			in the given given bit field.
 * 			If one of the following is encoutered:
 * 			- an unknown option.
 * 			- a non-argument token.
 * 			- the end of the token list.
 * 			Then the parsing stops and the function returns.
 * 
 * @param	token The first node of the linked list containing the arguments.
 * @param	opt The bit field where the options shall be saved.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an unknown option is encountered.
 */
inline static int	__get_opt(t_token const **const token, uint8_t *const opt)
{
	unsigned int	i;

	*opt = 0U;
	while (*token && *(*token)->str == '-')
	{
		i = __match_opt((*token)->str);
		if (!g_opt[i].str)
			return (EXIT_FAILURE);
		*opt |= g_opt[i].bit;
		*token = (*token)->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Proceed to change the current working directory to the provided
 * 			new one.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	dir The new working directory to go to.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__goto_specific_directory(
	t_env_lst *const env,
	char const *const dir)
{
	char *const	curpath = raw_curpath(env, dir);

	if (!curpath || canonicalize(curpath))
		return (free(curpath), EXIT_FAILURE);
	return (free(curpath), EXIT_SUCCESS);
}

/**
 * @brief	Change the current working directory to the one specified in the
 * 			first argument of the token. If more than 1 argument is provided,
 * 			if the first argument refers to an invalid path,
 * 			or if no argument is provided and the HOME environment variable
 * 			is not set, then the current working directory is kept unchanged,
 * 			and an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	builtin_cd(t_env_lst *const env, t_token const *token)
{
	uint8_t	opt;
	t_env	*node;

	if (__get_opt(&token, &opt))
		return (invalid_option_error("cd", token->str));
	if (token)
	{
		if (token->next)
			return (too_many_arguments_error("cd"));
		return (__goto_specific_directory(env, token->str));
	}
	node = env_lst_get_one(env, "HOME");
	if (!node || !*node->value)
		return (home_not_set_error("cd"));
	return (__goto_specific_directory(env, node->value));
}
