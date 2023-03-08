# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 12:46:31 by mcourtoi          #+#    #+#              #
#    Updated: 2023/03/02 03:26:30 by mcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

LIBFT_PATH = ./libft
LIBFT = ${LIBFT_PATH}/libft.a

SRC_DIR = srcs
OBJ_DIR = objs

SRCS =	\
		${addprefix builtins/,	\
			env.c 				\
			pwd.c 				\
			echo.c 				\
			unset.c				\
			export.c			\
		}						\
		${addprefix tokens/,	\
			get_tokens.c		\
			expand_tokens.c		\
			classify_tokens.c	\
		}						\
		${addprefix here_doc/,	\
			here_doc.c			\
			here_tokens.c		\
		}						\
		main.c \
		signals.c \
		utils_env.c \
		commands.c \
		utils.c \

OBJS = ${SRCS:.c=.o}
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS))

INC = ./includes

FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

${NAME}:    libft ${OBJS}
	    ${CC} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

-include ${OBJ_DIR}/*.d

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	mkdir -p ${@D}
	${CC} -g3 ${FLAGS} -I${INC} -c $< -o $@

libft:
	make -C libft

all:    ${NAME}

clean:
	rm -rf ${OBJ_DIR}
	@make -C libft clean

fclean: clean
	rm -f ${NAME}
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft