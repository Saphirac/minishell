/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/30 02:56:53 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	__clear_shell(void)
					__attribute__((destructor));

uint8_t	g_exit_code = 0U;

inline static t_shell	*__shell(void)
{
	static t_shell	shell;

	return (&shell);
}

/**
 * @brief	Initialize a linked list of environment variables
 * 			from an array of strings.
 * 
 * @param	env The linked list to initialize.
 * @param	ep The array of strings to use to initialize the linked list.
 * 
 * @return	EXIT_SUCCESS if the linked list was successfully initialized, or
 * 			EXIT_FAILURE if an error occured.
 */
inline static int	__init_env(t_env_lst *const env, char const *const *ep)
{
	char	*ptr;

	while (*ep)
	{
		ptr = ft_strchr(*ep, '=');
		if (!ptr)
		{
			env_lst_clear(env);
			return (EXIT_FAILURE);
		}
		*ptr = 0;
		++ptr;
		if (env_lst_add_back(env, *ep, ptr))
		{
			env_lst_clear(env);
			return (EXIT_FAILURE);
		}
		++ep;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Free the allocated memory of the shell context.
 */
inline static void	__clear_shell(void)
{
	t_shell *const	shell = __shell();

	env_lst_clear(&shell->env);
	token_lst_clear(&shell->tokens);
	pid_lst_clear(&shell->pids);
	ft_memdel(&shell->line);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	main(int const ac, char const *const *const av, char const *const *const ep)
{
	t_shell *const	shell = __shell();

	if (ac != 1)
		return (usage_error(av[0]));
	if (__init_env(&shell->env, ep))
	{
		ft_putendl_fd("Error: failed to initialize environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		signal_handle_interactive();
		prompt(shell);
	}
}
