/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:36:31 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/10 20:17:13 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"

typedef struct s_shell		t_shell;

struct s_shell
{
	t_token_lst	tokens;
	t_env_lst	env;
	char		*line;
	char		*line_hd;
	char		*stock_hd;
};

#endif
