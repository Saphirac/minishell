/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:36:31 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 20:37:51 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell		t_shell;

struct s_shell
{
	char	*line;
	char	**tokens;
	char	**env;
	char	*l_hd;
	char	*stock_hd;
};

#endif