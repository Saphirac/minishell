/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:35:35 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 20:12:11 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_double_quotes(char *str, int i)
{
	int	len_token;

	len_token = 0;
	if (str[i] == '"')
	{
		len_token++;
		i++;
		if (str[i] == '"')
			return (len_token + 1);
		while (str[i] && str[i] != '"')
		{
			len_token++;
			i++;
			if (str[i] == '"')
				return (len_token + 1);
		}
		if (str[i] == '\0')
			return (-1);
	}
	return (len_token);
}

int	count_single_quotes(char *str, int i)
{
	int	len_token;

	len_token = 0;
	if (str[i] == 39)
	{
		i++;
		len_token++;
		if (str[i] == 39)
			return (len_token + 1);
		while (str[i] && str[i] != 39)
		{
			len_token++;
			i++;
			if (str[i] == 39)
				return (len_token + 1);
		}
		if (str[i] == '\0')
			return (-1);
	}
	return (len_token);
}

int	count_quotes(char *str, int i)
{
	if (count_double_quotes(str, i) > 0)
		return (count_double_quotes(str, i));
	else if (count_single_quotes(str, i) > 0)
		return (count_single_quotes(str, i));
	else if (count_double_quotes(str, i) < 0 || count_single_quotes(str, i) < 0)
		return (-1);
	else
		return (0);
}

/*void	ftft(int *const n)
{
	for (int m = 0 ; m < 10 ; ++m)
		++*n;
}*/

int	count_tokens(char *str)
{
	int	i;
	int	nb_tokens;

	i = 0;
	nb_tokens = 0;
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (!str[i])
			return (nb_tokens);
		while (str[i] != ' ' && str[i] != '"' && str[i] != '\'' && str[i])
			i++;
		if (!str[i])
			return (nb_tokens + 1);
		if (str[i] == ' ')
			nb_tokens++;
		if (count_quotes(str, i) > 0)
			nb_tokens++;
		else if (count_quotes(str, i) < 0)
			return (printf("Error : Invalid syntax.\n"), -1);
		i += count_quotes(str, i);
	}
	return (nb_tokens);
}
