/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:07:41 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 19:12:20 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Makes an another pointer so we can free it
 * 	and not have leaks with ft_strjoin().
 * 
 * @param str0 string to join to.
 * @param str1 string joined.
 * @return char* new string resulting in the concatenation of the two strings.
 */
static inline char	*__leak_free_join(char const *const str0,
		char const *const str1)
{
	char	*result;

	result = ft_strjoin(str0, str1);
	return (free((void *)str0), result);
}

/**
 * @brief Appends or ft_strdup() either a given string
 * to the ret string and if given string is NULL,
 * append the str to the ret or ft_strdup() if ret is empty.
 * 
 * @param ret string which is ft_strdup() or ft_strjoin in this function.
 * @param tmp if tmp exists, ft_strdup() or ft_strjoin from this string.
 * @param str appends or join from this string if tmp does not exists.
 * (or some other exceptions.)
 * @param i struct t_tmp_i_start containing :
 * a start point for strndup and an iterator (i).
 * @return EXIT_FAILURE on malloc fail and EXIT_SUCCESS else.
 */
int	append_to_ret(char **ret, char const *const tmp,
		char *str, t_tmp_i_start *i)
{
	char	*tmp_2;

	if (i->i == 0 && str[i->i + 1] == '\0')
		*ret = ft_strdup(str);
	else if (i->i == 0)
		*ret = ft_strdup("");
	else if (!*ret && !tmp)
		*ret = ft_strndup(str + i->start, i->i - i->start);
	else if (!*ret)
		*ret = ft_strdup(tmp);
	else if (!tmp)
	{
		tmp_2 = ft_strndup(str + i->start, i->i - i->start);
		if (!tmp_2)
			return (EXIT_FAILURE);
		*ret = __leak_free_join(*ret, tmp_2);
		return (free(tmp_2), *ret == NULL);
	}
	else
		*ret = __leak_free_join(*ret, tmp);
	return (*ret == NULL);
}
