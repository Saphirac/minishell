/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:41:10 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/02 04:27:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_redirect	t_redirect;
typedef int					(*t_func1)(char const *const str);

struct	s_redirect
{
	t_token_type	type;
	t_func1			func;
};

static inline int	__redirect_stdin_from_file(char const *const str)
					__attribute__((nonnull));
static inline int	__redirect_stdin_from_heredoc(char const *const str)
					__attribute__((nonnull));
static inline int	__redirect_stdout_to_file_in_truncate_mode(
						char const *const str)
					__attribute__((nonnull));
static inline int	__redirect_stdout_to_file_in_append_mode(
						char const *const str)
					__attribute__((nonnull));

static t_redirect const		g_redirect[] = {
{T_INPUT, &__redirect_stdin_from_file},
{T_HEREDOC, &__redirect_stdin_from_heredoc},
{T_OUTPUT_TRUNCATE, &__redirect_stdout_to_file_in_truncate_mode},
{T_OUTPUT_APPEND, &__redirect_stdout_to_file_in_append_mode},
{0}
};

/**
 * @brief	Redirect stdin from a file.
 * 			If an error occurs, the exit status is set accordingly,
 * 			and an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdin from.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
static inline int	__redirect_stdin_from_file(char const *const str)
{
	int	fd;

	if (access(str, F_OK) || access(str, R_OK))
		return (g_exit_code = 1U, perror(str), EXIT_SUCCESS);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (g_exit_code = 1U, perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (g_exit_code = 1U, close(fd), perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdin from a heredoc.
 * 			If an error occurs, the exit status is set accordingly,
 * 			and an error message is output on stderr.
 * 
 * @param	str The content of the heredoc to redirect on stdin.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
static inline int	__redirect_stdin_from_heredoc(char const *const str)
{
	int	fds[2];

	if (pipe(fds))
		return (g_exit_code = 1U, perror("pipe()"), EXIT_FAILURE);
	if (write(fds[1], str, ft_strlen(str)) == -1)
		return (g_exit_code = 1U, close(fds[0]), close(fds[1]),
			perror("write()"), EXIT_FAILURE);
	if (close(fds[1]))
		return (g_exit_code = 1U, close(fds[0]), perror("close()"),
			EXIT_FAILURE);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (g_exit_code = 1U, close(fds[0]), perror("dup2()"),
			EXIT_FAILURE);
	if (close(fds[0]))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdout to a file in truncate mode.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdout to.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
static inline int	__redirect_stdout_to_file_in_truncate_mode(
	char const *const str)
{
	int	fd;

	if (!access(str, F_OK) && access(str, W_OK))
		return (g_exit_code = 1U, perror(str), EXIT_SUCCESS);
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (g_exit_code = 1U, perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (g_exit_code = 1U, perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdout to a file in append mode.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdout to.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
static inline int	__redirect_stdout_to_file_in_append_mode(
	char const *const str)
{
	int	fd;

	if (!access(str, F_OK) && access(str, W_OK))
		return (g_exit_code = 1U, perror(str), EXIT_SUCCESS);
	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (g_exit_code = 1U, perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (g_exit_code = 1U, close(fd), perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (g_exit_code = 1U, perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Apply input redirections from a file/heredoc,
 * 			and output redirections to a file.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	tokens The token list containing the redirections to apply.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if a fatal error occured.
 */
int	file_redirections(t_token_lst *const tokens)
{
	t_token const	*node = tokens->head;
	unsigned int	i;

	while (node)
	{
		i = 0U;
		while (g_redirect[i].func && node->type != g_redirect[i].type)
			++i;
		if (g_redirect[i].func)
		{
			if (!node->next || node->next->type != T_FILE)
				return (ambiguous_redirect_error(NULL));
			if (g_redirect[i].func(node->next->str))
				return (EXIT_FAILURE);
			if (g_exit_code)
				break ;
			node = token_lst_del_range(tokens, node, node->next->next);
		}
		else
			node = node->next;
	}
	return (EXIT_SUCCESS);
}
