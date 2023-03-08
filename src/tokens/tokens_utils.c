/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:29:36 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/09 03:46:52 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if character is a POSIX operator 
return 0 if true 
return 1 if false */

int	ft_is_op(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

/* Check if character is a space, an operator, EOF or a single / double quotes 
return 0 if true 
return 1 if false */

int	ft_is_sep(char c)
{
	if (c == '\0' || c == ' ' || c == '"' || c == '\'')
		return (0);
	else if (ft_is_op(c) == 0)
		return (0);
	return (1);
}
