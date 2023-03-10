/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/10 18:44:52 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

void	test_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("token %d : %s\n", i, str[i]);
		i++;
	}
}

char	**mini_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	env[1] = ft_strdup("PWD=/Users/minishell");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

void	prompt(t_shell *shell)
{
	int		exit_code;

	shell->line = readline("minishell $> ");
	if (!shell->line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_FAILURE);
	}
	if (shell->line[0] == '\n')
		write(STDOUT_FILENO, "\nminishell $> ", 14);
	if (ft_strlen(shell->line))
		add_history(shell->line);
	exit_code = tokens_get(shell);
	if (exit_code == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (exit_code == EXIT_SUCCESS)
		print_tokens(&(shell->tokens));
	token_lst_clear(&(shell->tokens));
	free(shell->line);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	ft_bzero(&shell, sizeof(t_shell));
	while (1)
	{
		signal_handle_interactive();
		prompt(&shell);
	}
	return (0);
}
