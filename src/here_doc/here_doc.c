/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/03/03 17:28:58 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	czeck_hd(char *str)
// {
// 	char	hd[2] = "<<";

// 	if (ft_strncmp(str, hd, 2) == 0)
// 		return (1);
// 	return (0);
// }

char	*get_hd(t_shell *shell, char *stop_signal)
{	
	shell->l_hd = readline("> ");
	if (!shell->l_hd)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_FAILURE);
	}
	while (shell->l_hd && ft_strncmp(shell->l_hd, stop_signal, ft_strlen(shell->l_hd)))
	{
		//signal_handle_heredoc();
		shell->stock_hd = stock_hd(shell);
		free(shell->l_hd);
		shell->l_hd = readline("> ");
	}
	free(shell->l_hd);
	return (shell->stock_hd);
}

