/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_builtin.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:29:22 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/08 20:45:03 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOKUP_BUILTIN_H
# define LOOKUP_BUILTIN_H

# include "minishell.h"

typedef struct s_builtin	t_builtin;
typedef int					(*t_func)(t_shell *const shell);

struct s_builtin
{
	char const *const	name;
	t_func const		func;
};

int	cd(t_shell *const shell)
	__attribute__((nonnull));
int	echo(t_shell *const shell)
	__attribute__((nonnull));
int	env(t_shell *const shell)
	__attribute__((nonnull));
int	exit(t_shell *const shell)
	__attribute__((nonnull));
int	export(t_shell *const shell)
	__attribute__((nonnull));
int	pwd(t_shell *const shell)
	__attribute__((nonnull));
int	unset(t_shell *const shell)
	__attribute__((nonnull));

static t_builtin const		g_builtin[] = {
{"cd", cd},
{"echo", echo},
{"env", env},
{"exit", exit},
{"export", export},
{"pwd", pwd},
{"unset", unset},
{0},
};

#endif
