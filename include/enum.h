/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:22:24 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/03 00:00:25 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

# include "minishell.h"

/* Used to classify each encountered tokens. */

typedef enum e_token_type	t_token_type;

enum	e_token_type
{
	T_WORD,
	T_OPERATOR,
	T_FILE,
	T_PIPE,
	T_INPUT,
	T_HEREDOC,
	T_OUTPUT_TRUNCATE,
	T_OUTPUT_APPEND,
	T_OPTION,
	T_BUILTIN,
	T_COMMAND,
	T_ARGUMENT,
	T_DELIMITER,
	T_DELIMITER_QUOTED,
	T_CONTENT,
	T_UNDEFINED,
	T_TO_SUPPR,
};

#endif
