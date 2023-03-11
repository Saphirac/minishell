/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/11 07:07:16 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_io.h"
# include "ft_string.h"
# include "enum.h"
# include "list.h"
# include "shell.h"
# include "lookup_builtin.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_ERROR 2

extern uint8_t	g_exit_code;

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

// Tokens //
int		ft_is_sep(char c);
int		ft_is_op(char c);
char	*ft_get_operator(t_shell *shell, int *i, int j);
void	print_tokens(t_token_lst *tokens);
int		tokens_get(t_shell *shell);
int		classify_tokens(t_shell *shell);
int		ft_if_pipe(t_token *tmp, bool *cmd);
int		ft_if_heredoc(t_token *tmp, bool *cmd);
int		ft_if_output_input(t_token *tmp, bool *cmd);
int		ft_if_operator(t_token *tmp, bool *cmd);
int		ft_if_command(t_token *tmp, bool *cmd);

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
