/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:23:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/10 01:13:54 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stddef.h>

typedef struct s_env		t_env;
typedef struct s_env_lst	t_env_lst;

struct s_env_lst
{
	t_env	*head;
	t_env	*tail;
	size_t	size;
};

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
	t_env	*prev;
};

/* lst functions for env_lst and env nodes */

void	env_lst_clear(t_env_lst *const list)
		__attribute__((nonnull));
void	env_lst_del_one(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));
void	env_lst_print(t_env_lst const *const list)
		__attribute__((nonnull));
void	env_lst_push_back(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));
void	env_lst_push_front(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));

int		env_lst_add_back(
			t_env_lst *const list,
			char const *const name,
			char const *const value)
		__attribute__((nonnull));
int		env_lst_add_front(
			t_env_lst *const list,
			char const *const name,
			char const *const value)
		__attribute__((nonnull));

t_env	*env_new(char const *const name, char const *const value)
		__attribute__((nonnull));

#endif
