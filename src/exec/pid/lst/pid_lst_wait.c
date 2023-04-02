/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:56:23 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 00:50:28 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_signaled_str	t_signaled_str;

struct s_signaled_str
{
	int const			sig;
	char const *const	str;
};

static t_signaled_str const		g_signaled_str[] = {
{SIGQUIT, "Quit (core dumped)"},
{SIGSEGV, "Segmentation fault (core dumped)"},
{SIGINT, ""},
{0}
};

/**
 * @brief	Set the exit code to the signal number + 128,
 * 			and output the corresponding message on stderr.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	status The raw status returned by waitpid().
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__signaled_suprocess(int const status)
{
	unsigned int	i;

	g_exit_code = (uint8_t)(128 + WTERMSIG(status));
	i = 0U;
	while (g_signaled_str[i].sig)
	{
		if (g_signaled_str[i].sig == WTERMSIG(status))
		{
			if (ft_putendl_fd(g_signaled_str[i].str, STDERR_FILENO) == -1)
				return (internal_error("ft_putendl_fd()"));
			break ;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Wait for all the processe ids contained in the given pid list,
 * 			and clear it at the same time. The exit code is set to the
 * 			exit code of the last process waited.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	list The list to wait processe ids from.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	pid_lst_wait(t_pid_lst *const list)
{
	int	status;

	while (list->size)
	{
		if (waitpid(list->head->pid, &status, 0) == -1)
			return (g_exit_code = 1U, internal_error("waitpid()"));
		pid_lst_del_one(list, list->head);
	}
	if (WIFEXITED(status))
		g_exit_code = (uint8_t)WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && __signaled_suprocess(status))
		return (EXIT_FAILURE);
	else if (WIFSTOPPED(status))
		g_exit_code = (uint8_t)WSTOPSIG(status);
	else
		g_exit_code = (uint8_t)status;
	return (EXIT_SUCCESS);
}
