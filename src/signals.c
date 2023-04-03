/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:53:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 06:03:14 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	g_exit_code = 128 + sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	if (rl_on_new_line())
		perror("rl_on_new_line()");
	rl_redisplay();
}

int	signal_handle_interactive(void)
{
	if (signal(SIGINT, &handle_signal) == SIG_ERR)
		return (EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	signal_default(void)
{
	int	i;

	i = 1;
	while (i < __SIGRTMIN)
	{
		if (i != SIGKILL && i != SIGSTOP && i != SIGCHLD
			&& signal(i, SIG_DFL) == SIG_ERR)
			return (g_exit_code = 1U, perror("signal()"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	signal_ignore(void)
{
	int	i;

	i = 1;
	while (i < __SIGRTMIN)
	{
		if (i != SIGKILL && i != SIGSTOP && i != SIGCHLD
			&& signal(i, SIG_IGN) == SIG_ERR)
			return (g_exit_code = 1U, perror("signal()"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
