/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:53:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:08:10 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Classic handle signal for SIGINT in interactif mode.
 * 
 * @param sig received.
 */
void	handle_signal(int sig)
{
	g_exit_code = 128 + sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	if (rl_on_new_line())
		perror("rl_on_new_line()");
	rl_redisplay();
}

/**
 * @brief Defines wanted comportment for SIGINT and SIGQUIT.
 * 
 * @return EXIT_FAILURE if signal() fails, EXIT_SUCCESS else.
 */
int	signal_handle_interactive(void)
{
	if (signal(SIGINT, &handle_signal) == SIG_ERR)
		return (perror("signal()"), EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (perror("signal()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Puts all signals back to their default comportment except :
 * SIGKILL, SIGSTOP and SIGCHLD.
 * 
 * @return EXIT_FAILURE if signal() fails, EXIT_SUCCESS else.
 */
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

/**
 * @brief Puts all signal comportment to ignore except :
 * SIGKILL, SIGSTOP and SIGCHLD.
 * 
 * @return EXIT_FAILURE if signal() fails, EXIT_SUCCESS else.
 */
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
