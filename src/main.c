/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:48:12 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 23:53:42 by mcourtoi         ###   ########.fr       */
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
	/*char	*tmp;*/

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
	if (count_tokens(shell->line) > 0)
	{
		shell->tokens = tokens_tab(shell, 0);
		test_tab(shell->tokens);
		ft_free(shell->tokens);
	}
	/*tmp = search_env(shell->env, shell->tokens[1]);
	if (tmp)
		printf("%s\n", expand_dollar(shell->tokens[1], tmp));
	free(tmp);*/
	free(shell->line);
}

void	init_lst(t_shell *shell)
{
	ft_bzero(shell->tokens, sizeof(t_token_lst));
	ft_bzero(shell->env, sizeof(t_env_lst));
	//ft_get_env(shell->env);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	while (1)
	{
		signal_handle_interactive();
		prompt(&shell);
		/* get_hd(&shell, "stop");
		printf("%s", shell.stock_hd); */
	}
	return (0);
}
