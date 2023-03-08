/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/07 21:14:13 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtins.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_code;

typedef struct s_token t_token;
typedef struct s_shell t_shell;
typedef struct s_token_lst t_token_lst;
typedef struct s_env t_env;
typedef struct s_env_lst t_env_lst;

struct s_shell
{
	char	*line;
	char	**tokens;
	char	**env;
	char	*l_hd;
	char	*stock_hd;
};

struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
};

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
	t_token	*prev;
};

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

void	free_tab(char **tab);
void	handle_signal(int sig);
void	signal_handle_interactive(void);
void	signal_handle_non_interactive(void);
int		count_tokens(char *str);
int		count_quotes(char *str, int i);
char	**tokens_tab(t_shell *shell, int i);
char	**get_commands(t_shell *shell);
char	*expand_single_quotes(char *token);
char	*expand_double_quotes(t_shell *shell, char *token);
char	*search_env(char **env, char *token);
char	*expand_dollar(char *token, char *tmp);

// Utils //
void	ft_free(char **tab);
char	*access_path(char **paths, char *cmd);
char	*add_path(char *str, char *av1, char c);
char	*find_apath(char **env);

// Heredoc
char	*stock_hd(t_shell *shell);
void	signal_handle_heredoc(void);
char	*get_hd(t_shell *shell, char *stop_signal);

#endif