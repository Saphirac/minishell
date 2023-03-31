/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/31 04:18:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "ft_io.h"
# include "ft_colors.h"
# include "ft_string.h"
# include "enum.h"
# include "list.h"
# include "shell.h"
# include "lookup_builtin.h"

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_ERROR 2

extern uint8_t	g_exit_code;

void	prompt(t_shell *const shell)
		__attribute__((nonnull));
void	handle_signal(int sig);
void	signal_handle_interactive(void);
void	signal_handle_non_interactive(void);

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

// Execution //
int		execution(t_shell *const shell)
		__attribute__((nonnull));
int		redirections(t_token_lst *const tokens, int const fd)
		__attribute__((nonnull));
int		run(t_shell *const shell)
		__attribute__((nonnull));

// Builtins //
int		canonicalize(char *const curpath)
		__attribute__((nonnull));
int		surprise(void);

bool	is_directory(char const *const pathname)
		__attribute__((nonnull));

char	*raw_curpath(t_env_lst const *const env, char const *const dir)
		__attribute__((nonnull));

// Errors //
int		command_not_found_error(char const *const cmd)
		__attribute__((nonnull));
int		home_not_set_error(char const *const str)
		__attribute__((nonnull));
int		internal_error(char const *const str)
		__attribute__((nonnull));
int		invalid_option_error(char const *const str, char const *const opt)
		__attribute__((nonnull));
int		no_such_file_or_directory_error(
			char const *const str,
			char const *const path)
		__attribute__((nonnull (2)));
int		permission_denied_error(char const *const str)
		__attribute__((nonnull));
int		too_many_arguments_error(char const *const str)
		__attribute__((nonnull));

// Heredoc
char	*stock_hd(t_shell *shell);
void	signal_handle_heredoc(void);
char	*get_hd(t_shell *shell, char *stop_signal);

#endif
