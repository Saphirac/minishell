/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:35:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/25 17:43:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Check whether the given string represents a positive integer.
 * 
 * @param	str The string to check.
 * 
 * @return	Whether the given string represents a positive integer.
 */
inline static bool	__is_positive(char const *str)
{
	if (*str == '+')
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		++str;
	}
	return (true);
}

/**
 * @brief	Exit the shell, with either the given status code as argument,
 * 			or the last saved status code.
 * 			If the argument count is greater than 1,
 * 			the shell is not exited, and an error is output.
 * 			If the argument contains a non-numerical character,
 * 			the shell is exited, and an error is output.
 * 			If the argument value is outside of the range [0 ; 255],
 * 			the shell is exited with an undefined exit status code.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments.
 * 
 * @return	The function shall call `exit` and therefore shall never return,
 * 			except in case of error where EXIT_FAILURE is returned.
 */
int	builtin_exit(t_env_lst *const env, t_token const *token)
{
	char	*str;

	if (!env_lst_get_one(env, "QUIET_EXIT"))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (token)
	{
		str = ft_strtrim(token->str, " \t");
		if (!str)
			return (internal_error("exit: ft_strtrim()"));
		if (!__is_positive(str))
		{
			ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				str);
			free(str);
			exit(2);
		}
		if (token->next)
		{
			free(str);
			return (too_many_arguments_error("exit"));
		}
		g_exit_code = ft_atohhu(str);
		free(str);
	}
	exit(g_exit_code);
}
