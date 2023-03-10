/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:38 by maparigi          #+#    #+#             */
/*   Updated: 2023/03/10 20:04:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

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
	shell->line_hd = readline("> ");
	if (!shell->line_hd)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_FAILURE);
	}
	while (shell->line_hd && ft_strncmp(shell->line_hd,
			stop_signal, ft_strlen(shell->line_hd)))
	{
		//signal_handle_heredoc();
		shell->stock_hd = stock_hd(shell);
		free(shell->line_hd);
		shell->line_hd = readline("> ");
	}
	free(shell->line_hd);
	return (shell->stock_hd);
}

*/
