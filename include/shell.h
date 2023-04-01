/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:36:31 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/02 00:21:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef struct s_shell	t_shell;

struct s_shell
{
	t_token_lst	tokens;
	t_env_lst	env;
	t_pid_lst	pids;
	char		*line;
	bool		is_pipeline;
	int			stdin_backup;
	int			stdout_backup;
};

#endif
