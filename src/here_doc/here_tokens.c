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

char	*get_eof(char *ret)
{
	char	*tmp_ptr;

	tmp_ptr = ret;
	ret = ft_strjoin(ret, "\n");
	if (!ret)
		return (free(tmp_ptr), NULL);
	return (free(tmp_ptr), ret);
}

int	stock_hd(char *line, char **ret)
{
	char	*tmp_ptr;
	if (!*ret)
	{
		*ret = ft_strdup(line);
		if (!*ret)
			return (EXIT_FAILURE);
	}
	else
	{
		tmp_ptr = *ret;
		*ret = ft_strjoin(*ret, line);
		if (!*ret)
			return (free(tmp_ptr), EXIT_FAILURE);
		free(tmp_ptr);
	}
	ret = get_eof(ret);
	if (!ret)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
