/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_builtin.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:29:22 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/03 06:55:51 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOKUP_BUILTIN_H
# define LOOKUP_BUILTIN_H

# include "minishell.h"

typedef struct s_builtin	t_builtin;
typedef void				(*t_func0)(t_env_lst *const, t_token const *const);

struct s_builtin
{
	char const *const	name;
	t_func0 const		func;
};

void	builtin_cd(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_echo(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_env(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_exit(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_export(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_pwd(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));
void	builtin_unset(t_env_lst *const env, t_token const *token)
		__attribute__((nonnull (1)));

static t_builtin const		g_builtin[] = {
{"cd", builtin_cd},
{"echo", builtin_echo},
{"env", builtin_env},
{"exit", builtin_exit},
{"export", builtin_export},
{"pwd", builtin_pwd},
{"unset", builtin_unset},
{0},
};

#endif
