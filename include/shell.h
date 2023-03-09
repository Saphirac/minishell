/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:36:31 by mcourtoi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/08 23:52:10 by mcourtoi         ###   ########.fr       */
=======
/*   Updated: 2023/03/08 20:37:51 by mcourtoi         ###   ########.fr       */
>>>>>>> 6c4dd57d694eba7e50686c6cd4cd62806e855431
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell		t_shell;

struct s_shell
{
<<<<<<< HEAD
	t_token_lst	*tokens;
	t_env_lst	**env;
	char		*line;
	char		*line_hd;
	char		*stock_hd;
=======
	char	*line;
	char	**tokens;
	char	**env;
	char	*l_hd;
	char	*stock_hd;
>>>>>>> 6c4dd57d694eba7e50686c6cd4cd62806e855431
};

#endif