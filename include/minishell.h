/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:55:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/22 02:31:22 by mcourtoi         ###   ########.fr       */
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
# include <stdbool.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_ERROR 2

extern uint8_t	g_exit_code;

void	handle_signal(int sig);
void	signal_handle_interactive(void);
void	signal_handle_non_interactive(void);
int		count_tokens(char *str);
int		count_quotes(char *str, int i);
char	**tokens_tab(t_shell *shell, int i);
char	**get_commands(t_shell *shell);
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
int		ft_env_cpy(char *env_value, char *tmp, char *cmp);
int		create_str_lst(t_token *token, t_str_lst *str_lst);
int		expand_dollars_str_lst(t_env_lst *env_lst, t_str_lst *str_lst);
int		add_str_to_token(t_token_lst *const token_lst, t_token *const token,
			t_str_lst *const str);
int		final_token_lst(t_token_lst *token_lst, t_env_lst *env_lst);

// Utils //
void	ft_free(char **tab);
char	*access_path(char **paths, char *cmd);
char	*add_path(char *str, char *av1, char c);
char	*find_apath(char **env);
int		surprise(void);
int		usage_error(char const *const prog_name)
		__attribute__((nonnull));
int		internal_error(char const *const str)
		__attribute__((nonnull));

// Heredoc
char	*stock_hd(t_shell *shell);
void	signal_handle_heredoc(void);
char	*get_hd(t_shell *shell, char *stop_signal);

#endif
