/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:33:56 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/11 19:47:34 by jodufour         ###   ########.fr       */
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

inline static uint8_t	__get_opt(t_token const **const token)
{
	uint8_t			opt;
	unsigned int	i;

	opt = 0U;
	while (*token && (*token)->type == T_ARGUMENT)
	{
		i = __match_opt((*token)->str);
		if (!g_opt[i].str)
			break ;
		opt |= g_opt[i].bit;
		*token = (*token)->next;
	}
	return (opt);
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
 * @return	The updated exit status.
 */
int	builtin_echo(
	t_env_lst *const env __attribute__((unused)),
	t_token const *token)
{
	uint8_t	opt;

	opt = __get_opt(&token);
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
