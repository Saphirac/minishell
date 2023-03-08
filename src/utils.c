/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:58:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/02/06 17:59:53 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*access_path(char **paths, char *cmd)
{
	char	*apath;
	int		i;

	i = -1;
	while (paths[++i])
	{
		apath = add_path(paths[i], cmd, '/');
		if (access(apath, F_OK) == 0)
			return (apath);
		free(apath);
	}
	return (NULL);
}

char	*add_path(char *str, char *av1, char c)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (str)
	{
		dst = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(av1) + 2));
		if (!dst)
			return (NULL);
		while (str[++i])
			dst[i] = str[i];
		dst[i++] = c;
		while (av1[++j])
			dst[i++] = av1[j];
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}

char	*find_apath(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=/", 6) == 0)
			return (env[i] + 5);
	return (NULL);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
