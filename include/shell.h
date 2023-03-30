/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:36:31 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/28 20:30:08 by mcourtoi         ###   ########.fr       */
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
	char		*line;
	bool		is_pipeline;
};

#endif
