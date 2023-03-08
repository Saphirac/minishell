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

char	*ft_strjoin_hd(char const *s1, char const *s2)
{
	char	*dest;
	size_t	ma;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	ma = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * (ma + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\n';
	dest[i + 1] = '\0';
	return (dest);
}

char	*ft_strdup_hd(const char *s)
{
	size_t	i;
	char	*cpy;

	cpy = malloc(sizeof(const char) * (ft_strlen(s) + 2));
	if (!cpy)
		return (NULL);
	i = -1;
	while (s[++i])
		cpy[i] = ((char *)s)[i];
	cpy[i] = '\n';
	cpy[i + 1] = '\0';
	return (cpy);
}

char	*stock_hd(t_shell *shell)
{
	if (!shell->stock_hd && shell->l_hd)
	{
		shell->stock_hd = ft_strdup_hd(shell->l_hd);
		if (!shell->stock_hd)
			return (NULL);
		return (shell->stock_hd);
	}
	else if (shell->stock_hd && shell->l_hd)
	{
		shell->stock_hd = ft_strjoin_hd(shell->stock_hd, shell->l_hd);
		if (!shell->stock_hd)
			return (NULL);
		return (shell->stock_hd);
	}
	return (NULL);
}
