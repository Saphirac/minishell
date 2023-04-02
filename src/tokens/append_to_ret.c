/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:07:41 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/02 03:32:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*__leak_free_join(char const *const str0,
		char const *const str1)
{
	char	*result;

	result = ft_strjoin(str0, str1);
	return (free((void *)str0), result);
}

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
