/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surprise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:15:18 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/12 16:20:30 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char const	g_surprise[] = "\
           .-.\n\
          |   |\n\
          |   |\n\
       ,-'|   |)\n\
      /,-.|   |,-. __\n\
     /|   |   |   |  ;\n\
    | |   |   |   |  ;\n\
    | |   |   |      |\n\
     \\|             ,/\n\
      '-.________.-'\n";

/**
 * @brief	This is our own undefined behavior of builtin export
 * 			when called without any argument. Try it yourself! ;D
 * 
 * @return	Always EXIT_SUCCESS.
 */
int	surprise(void)
{
	printf("%s", g_surprise);
	return (EXIT_SUCCESS);
}
