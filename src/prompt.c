/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:46:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/23 23:45:07 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	__make_tests(t_shell *const shell)
{
	print_tokens(&shell->tokens);
	if (execution(shell))
		exit(EXIT_FAILURE);
}

/**
 * @brief	Display the prompt and get the user inpuredirectionst.
 * 			Then, when the user press enter, the input is processed.
 * 
 * @param	shell The context which contains the program's data.
 */
void	prompt(t_shell *const shell)
{
	int	exit_code;

	shell->line = readline("minishell $> ");
	if (!shell->line && write(STDOUT_FILENO, (char [1]){'\n'}, 1LU))
		builtin_exit(&shell->env, NULL);
	if (*shell->line)
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
			__make_tests(shell);
	}
	token_lst_clear(&shell->tokens);
	ft_memdel(&shell->line);
}
