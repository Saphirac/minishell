# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 11:35:14 by jodufour          #+#    #+#              #
#    Updated: 2023/03/09 11:35:15 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VG_OPT	=	--suppressions=ignoreliberror
VG_OPT	+=	--leak-check=full
VG_OPT	+=	--show-leak-kinds=all
VG_OPT	+=	--track-fds=yes
VG_OPT	+=	--trace-children=yes

valgrind:
	${MAKE} ${NAME} DEBUG=1
	$@ ${VG_OPT} ./${NAME}

.PHONY: valgrind
