/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:18:12 by red               #+#    #+#             */
/*   Updated: 2023/03/08 18:51:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_strintab(char *str, char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 0)
			return (i);
	return (-1);
}

int	tab_val(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}
