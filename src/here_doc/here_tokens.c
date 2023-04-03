/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_tk_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:28:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/02/28 04:46:48 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Modified strjoin() that can take 3 strings.
 * Uses ft_memcpy() to concatenate them.
 * Useful to add the '\n' of heredoc.
 * 
 * @param a 1st string to concatenate to.
 * @param b 2nd string added to a.
 * @param c last string add to a and b.
 * @return result of the join.
 */
static inline char	*__strjoin_hd(
	char const *const a,
	char const *const b,
	char const *const c)
{
	size_t const	len_a = ft_strlen(a);
	size_t const	len_b = ft_strlen(b);
	size_t const	len_c = ft_strlen(c) + 1;
	char *const		ret = malloc(sizeof(char) * (len_a + len_b + len_c));

	if (!ret)
		return (NULL);
	ft_memcpy(ret, a, len_a);
	ft_memcpy(ret + len_a, b, len_b);
	ft_memcpy(ret + len_a + len_b, c, len_c);
	return (ret);
}

/**
 * @brief Copy or append the received line to ret.
 * 
 * @param line result from readline.
 * @param ret result to be added in token.
 * @return EXIT_FAILURE if malloc fail, EXIT_SUCCESS else.
 */
int	stock_hd(char const *const line, char **const ret)
{
	char	*tmp_ptr;

	tmp_ptr = *ret;
	if (!**ret)
		*ret = ft_strjoin(line, "\n");
	else
		*ret = __strjoin_hd(*ret, line, "\n");
	if (!*ret)
		return (*ret = tmp_ptr, EXIT_FAILURE);
	return (free(tmp_ptr), EXIT_SUCCESS);
}
