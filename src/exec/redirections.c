/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:41:10 by jodufour          #+#    #+#             */
/*   Updated: 2023/04/01 03:16:27 by jodufour         ###   ########.fr       */
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
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdin from.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
static inline int	__redirect_stdin_from_file(char const *const str)
{
	int	fd;

	if (access(str, F_OK) || access(str, R_OK))
		return (perror(str), EXIT_FAILURE);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdin from a heredoc.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The content of the heredoc to redirect on stdin.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
static inline int	__redirect_stdin_from_heredoc(char const *const str)
{
	int	fds[2];

	if (pipe(fds))
		return (perror("pipe()"), EXIT_FAILURE);
	if (write(fds[1], str, ft_strlen(str)) == -1)
		return (close(fds[0]), close(fds[1]), perror("write()"), EXIT_FAILURE);
	if (close(fds[1]))
		return (close(fds[0]), perror("close()"), EXIT_FAILURE);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (close(fds[0]), perror("dup2()"), EXIT_FAILURE);
	if (close(fds[0]))
		return (perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdout to a file in truncate mode.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdout to.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
static inline int	__redirect_stdout_to_file_in_truncate_mode(
	char const *const str)
{
	int	fd;

	if (!access(str, F_OK) && access(str, W_OK))
		return (perror(str), EXIT_FAILURE);
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Redirect stdout to a file in append mode.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	str The name of the file to redirect stdout to.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
static inline int	__redirect_stdout_to_file_in_append_mode(
	char const *const str)
{
	int	fd;

	if (!access(str, F_OK) && access(str, W_OK))
		return (perror(str), EXIT_FAILURE);
	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open()"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2()"), EXIT_FAILURE);
	if (close(fd))
		return (perror("close()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Apply input and output redirections,
 * 			starting with the output pipe redirection,
 * 			then any input redirection from a file/heredoc,
 * 			and finaly any output redirection to a file.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	tokens The token list containing the redirections to apply.
 * @param	fd The file descriptor to use as stdout by default.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	redirections(t_token_lst *const tokens, int const fd)
{
	t_token const	*node = tokens->head;
	unsigned int	i;

	if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2()"), EXIT_FAILURE);
		if (close(fd))
			return (perror("close()"), EXIT_FAILURE);
	}
	while (node)
	{
		i = 0U;
		while (g_redirect[i].func && node->type != g_redirect[i].type)
			++i;
		if (g_redirect[i].func)
		{
			if (g_redirect[i].func(node->next->str))
				return (EXIT_FAILURE);
			node = token_lst_del_range(tokens, node, node->next->next);
		}
		else
			node = node->next;
	}
	return (EXIT_SUCCESS);
}
