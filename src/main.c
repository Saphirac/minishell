/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 04:21:35 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	__clear_shell(void)
					__attribute__((destructor));

uint8_t	g_exit_code = 0U;

inline static t_shell	*__shell(void)
{
	static t_shell	shell = {{0}, {0}, {0}, NULL, false, -1, -1};

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
			if (!env_lst_add_back(env, *ep, NULL))
				return (EXIT_FAILURE);
		}
		else
		{
			*ptr = 0;
			if (!env_lst_add_back(env, *ep, ptr + 1))
				return (EXIT_FAILURE);
			*ptr = '=';
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
	rl_clear_history();
	ft_fddel(&shell->stdin_backup);
	ft_fddel(&shell->stdout_backup);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	main(
	int const ac,
	char *const *const av __attribute__((unused)),
	char const *const *const ep)
{
	t_shell *const	shell = __shell();

	if (ac != 1)
	{
		ft_putendl_fd("Error: invalid number of arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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
