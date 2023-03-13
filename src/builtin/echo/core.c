/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:33:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 14:12:41 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_opt	t_opt;

enum	e_opt
{
	OPT_N,
};

struct	s_opt
{
	char const *const	str;
	uint8_t const		bit;
};

static t_opt const		g_opt[] = {
{"-n", 1 << OPT_N},
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
 */
inline static void	__get_opt(t_token const **const token, uint8_t *const opt)
{
	unsigned int	i;

	*opt = 0U;
	while (*token && (*token)->type == T_ARGUMENT && *(*token)->str == '-')
	{
		i = __match_opt((*token)->str);
		if (!g_opt[i].str)
			return ;
		*opt |= g_opt[i].bit;
		*token = (*token)->next;
	}
	return ;
}

/**
 * @brief	Print the given arguments to the standard output.
 * 			If an unknown option is given, it shall be considered
 * 			as an argument.
 * 
 * @details	The following options are supported:
 * 			-n: Do not output the trailing newline.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	Always EXIT_SUCCESS.
 */
int	builtin_echo(
	t_env_lst *const env __attribute__((unused)),
	t_token const *token)
{
	uint8_t	opt;

	__get_opt(&token, &opt);
	while (token && token->type == T_ARGUMENT)
	{
		printf("%s", token->str);
		token = token->next;
		if (token && token->type == T_ARGUMENT)
			printf(" ");
	}
	if (!(opt & 1 << OPT_N))
		printf("\n");
	return (EXIT_SUCCESS);
}
