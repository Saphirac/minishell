/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:34:48 by red               #+#    #+#             */
/*   Updated: 2023/02/25 17:18:27 by red              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"

void		my_env(char **env);
void		my_echo(char *str, char	*bsn);

int			my_pwd(void);
int			tab_val(char **tab);
int			find_strintab(char *str, char **tab);

char		**my_unset(char *str, char **env);
char		**my_export(char *str, char **env);

#endif