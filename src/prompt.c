/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:46:52 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 05:20:52 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Display the prompt and get the user input.
 * 			Then, when the user press enter, the input is processed.
 * 
 * @param	shell The context which contains the program's data.
 */
void	prompt(t_shell *const shell)
{
	int	exit_code;

	shell->line = readline("minishell $> ");
	if (!shell->line)
		builtin_exit(&shell->env, NULL);
	if (*shell->line)
		add_history(shell->line);
	exit_code = tokens_get(shell);
	if (exit_code == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (exit_code == EXIT_SUCCESS)
	{
		exit_code = classify_tokens(shell);
		if (exit_code == EXIT_SUCCESS)
			exit_code = final_token_lst(&shell->tokens, &shell->env);
		if (exit_code == EXIT_SUCCESS)
		{
			final_classification(&shell->tokens, &shell->is_pipeline);
			exit_code = do_here_doc(&shell->tokens, &shell->env);
			if (exit_code == EXIT_SUCCESS && execution(shell))
				exit(EXIT_FAILURE);
		}
	}
	token_lst_clear(&shell->tokens);
	ft_memdel(&shell->line);
}
