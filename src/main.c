/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/25 06:11:22 by mcourtoi         ###   ########.fr       */
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
	int	exit_code;

	shell->line = readline("minishell $> ");
	if (!shell->line)
		exit(g_exit_code);
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
		exit_code = final_token_lst(&shell->tokens, &shell->env);
		if (exit_code == EXIT_SUCCESS)
			print_tokens(&shell->tokens);
		else
			exit (EXIT_FAILURE);
	}
	token_lst_clear(&shell->tokens);
	env_lst_clear(&shell->env);
	ft_memdel(&shell->line);
}

inline static void	__clear_shell(void)
{
	t_shell *const	shell = __shell();

	env_lst_clear(&shell->env);
	token_lst_clear(&shell->tokens);
	ft_memdel(&shell->line);
	ft_memdel(&shell->line_hd);
	ft_memdel(&shell->stock_hd);
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
		__prompt(shell);
	}
}
