/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/10 01:29:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_io.h"
# include "ft_string.h"
# include "list.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int					g_exit_code;

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_token_lst	t_token_lst;

struct s_shell
{
	char		*line;
	char		**tokens;
	t_env_lst	env;
	char		*l_hd;
	char		*stock_hd;
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
