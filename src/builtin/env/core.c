/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:34:59 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/13 20:58:49 by jodufour         ###   ########.fr       */
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
	while (*token && (*token)->type == T_ARGUMENT && *(*token)->str == '-')
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
 * @brief	Print all the current environment variables to the standard output.
 * 			Neither options nor arguments are supported.
 * 			If any are given, an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	builtin_env(t_env_lst *const env, t_token const *token)
{
	uint8_t	opt;

	if (__get_opt(&token, &opt))
	{
		ft_dprintf(STDERR_FILENO, "env: %s: invalid option\n", token->str);
		return (EXIT_FAILURE);
	}
	while (token && token->type == T_ARGUMENT)
	{
		ft_putstr_fd("env: too many arguments\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	env_lst_print_assigned(env);
	return (EXIT_SUCCESS);
}
