/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:23:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/27 01:41:22 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_token_lst	t_token_lst;
typedef struct s_env		t_env;
typedef struct s_env_lst	t_env_lst;
typedef struct s_pid		t_pid;
typedef struct s_pid_lst	t_pid_lst;

struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
};

struct s_token
{
	char			*str;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

struct s_env_lst
{
	t_env	*head;
	t_env	*tail;
	size_t	size;
};

struct s_env
{
	char const	*name;
	char const	*value;
	t_env		*next;
	t_env		*prev;
};

struct s_pid_lst
{
	t_pid	*head;
	t_pid	*tail;
	size_t	size;
};

struct s_pid
{
	int		pid;
	t_pid	*next;
	t_pid	*prev;
};

/* functions for token list and token nodes */

void	token_lst_clear(t_token_lst *const list)
		__attribute__((nonnull));
void	token_lst_del_one(t_token_lst *const list, t_token const *const node)
		__attribute__((nonnull));
void	token_lst_del_range(
			t_token_lst *const list,
			t_token const *begin,
			t_token const *const end)
		__attribute__((nonnull (1)));
void	token_lst_push_back(t_token_lst *const list, t_token *const node)
		__attribute__((nonnull));
void	token_lst_push_front(t_token_lst *const list, t_token *const node)
		__attribute__((nonnull));

int		token_lst_add_back(t_token_lst *const list, int const type,
			char *const str)
		__attribute__((nonnull));
int		token_lst_add_front(t_token_lst *const list, int const type,
			char *const str)
		__attribute__((nonnull));

bool	token_lst_is_first_builtin(t_token_lst const *const list)
		__attribute__((nonnull));

t_token	*token_lst_find_first_by_type(
			t_token_lst const *const list,
			t_token_type const type)
		__attribute__((nonnull));
t_token	*token_new(int const type, char *const str);

char	**token_lst_to_string_array(t_token_lst const *const list)
		__attribute__((nonnull));

/* functions for env list and env nodes */

void	env_lst_clear(t_env_lst *const list)
		__attribute__((nonnull));
void	env_lst_del_one(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));
void	env_lst_print_assigned(t_env_lst const *const list)
		__attribute__((nonnull));
void	env_lst_push_back(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));
void	env_lst_push_front(t_env_lst *const list, t_env *const node)
		__attribute__((nonnull));

int		env_lst_add_back(
			t_env_lst *const list,
			char const *const name,
			char const *const value)
		__attribute__((nonnull (1, 2)));
int		env_lst_add_front(
			t_env_lst *const list,
			char const *const name,
			char const *const value)
		__attribute__((nonnull (1, 2)));

t_env	*env_lst_get_one(t_env_lst const *const list, char const *const name)
		__attribute__((nonnull));
t_env	*env_new(char const *const name, char const *const value)
		__attribute__((nonnull (1)));

char	**env_lst_to_string_array(t_env_lst const *const list)
		__attribute__((nonnull));

/* functions for pid list and pid nodes */

void	pid_lst_clear(t_pid_lst *const list)
		__attribute__((nonnull));
void	pid_lst_del_one(t_pid_lst *const list, t_pid *const node)
		__attribute__((nonnull));
void	pid_lst_push_back(t_pid_lst *const list, t_pid *const node)
		__attribute__((nonnull));
void	pid_lst_push_front(t_pid_lst *const list, t_pid *const node)
		__attribute__((nonnull));

int		pid_lst_add_back(t_pid_lst *const list, int const pid)
		__attribute__((nonnull));
int		pid_lst_add_front(t_pid_lst *const list, int const pid)
		__attribute__((nonnull));
int		pid_lst_kill(t_pid_lst *const list, int const sig)
		__attribute__((nonnull));
int		pid_lst_wait(t_pid_lst const *const list)
		__attribute__((nonnull));

t_pid	*pid_new(int const pid);

#endif
