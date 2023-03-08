/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:18:12 by red               #+#    #+#             */
/*   Updated: 2023/02/21 15:22:34 by red              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
