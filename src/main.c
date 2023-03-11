/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/11 02:50:45 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

inline static int	__usage_error(char const *const prog_name)
					__attribute__((nonnull(1)));
inline static int	__init_env(t_env_lst *const env, char const *const *ep)
					__attribute__((nonnull(1, 2)));

inline static int	__usage_error(char const *const prog_name)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putendl_fd(prog_name, STDERR_FILENO);
	return (EXIT_FAILURE);
}

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

inline static void	__prompt(t_shell *const shell)
{
	int		exit_code;

	shell->line = readline("minishell $> ");
	if (!shell->line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		env_lst_clear(&shell->env);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(shell->line))
		add_history(shell->line);
	exit_code = tokens_get(shell);
	if (exit_code == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (exit_code == EXIT_SUCCESS)
	{
		exit_code = classify_tokens(shell);
		if (exit_code == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (exit_code == EXIT_SUCCESS)
			print_tokens(&shell->tokens);
	}
	token_lst_clear(&(shell->tokens));
	free(shell->line);
}

int	main(int const ac, char const *const *const av, char const *const *const ep)
{
	t_shell	shell;

	if (ac != 1)
		return (__usage_error(av[0]));
	ft_bzero(&shell, sizeof(t_shell));
	if (__init_env(&shell.env, ep))
	{
		ft_putendl_fd("Error: failed to initialize environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		signal_handle_interactive();
		__prompt(&shell);
	}
}
