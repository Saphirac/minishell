# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 12:46:31 by mcourtoi          #+#    #+#              #
#    Updated: 2023/03/10 20:16:08 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CC					=	cc -c
LINK				=	clang
MKDIR				=	mkdir -p
RM					=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME				=	minishell.out

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR				=	src
OBJ_DIR				=	obj
INC_DIR				=	include
PRV_DIR				=	private

FT_IO_DIR			=	libft_io
FT_IO_INC_DIR		=	include
FT_IO_INC_DIR		:=	${addprefix ${FT_IO_DIR}/, ${FT_IO_INC_DIR}}

FT_STRING_DIR		=	libft_string
FT_STRING_INC_DIR	=	include
FT_STRING_INC_DIR	:=	${addprefix ${FT_STRING_DIR}/, ${FT_STRING_INC_DIR}}

#######################################
#              LIBRARIES              #
#######################################
FT_IO_A				=	libft_io.a
FT_IO_A				:=	${addprefix ${FT_IO_DIR}/, ${FT_IO_A}}

FT_STRING_A			=	libft_string.a
FT_STRING_A			:=	${addprefix ${FT_STRING_DIR}/, ${FT_STRING_A}}

######################################
#            SOURCE FILES            #
######################################
SRC					=				\
	${addprefix builtin/,			\
		${addprefix cd/,			\
			core.c					\
		}							\
		${addprefix echo/,			\
			core.c					\
		}							\
		${addprefix env/,			\
			core.c					\
		}							\
		${addprefix exit/,			\
			core.c					\
		}							\
		${addprefix export/,		\
			core.c					\
		}							\
		${addprefix pwd/,			\
			core.c					\
		}							\
		${addprefix unset/,			\
			core.c					\
		}							\
	}								\
	${addprefix here_doc/,			\
		here_doc.c					\
		here_tokens.c				\
	}								\
	${addprefix tokens/,			\
		expand_tokens.c				\
		get_tokens.c				\
		tokens_operators.c			\
		tokens_utils.c				\
	}								\
	${addprefix tokens/lst_tokens/,	\
		token_lst_add_back.c		\
		token_lst_add_front.c 		\
		token_lst_clear.c			\
		token_lst_del_one.c			\
		token_lst_push_back.c		\
		token_lst_push_front.c		\
		token_new.c					\
	}								\
	commands.c						\
	main.c							\
	parse.c							\
	signals.c						\
	utils_env.c						\
	utils.c

######################################
#            OBJECT FILES            #
######################################
OBJ					=	${SRC:.c=.o}
OBJ					:=	${addprefix ${OBJ_DIR}/, ${OBJ}}

DEP					=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CFLAGS				=	-Wall -Wextra -Werror
CFLAGS				+=	-MMD -MP
CFLAGS				+=	-I${INC_DIR}
CFLAGS				+=	-I${FT_IO_INC_DIR}
CFLAGS				+=	-I${FT_STRING_INC_DIR}

LDFLAGS				=	-lreadline
LDFLAGS				+=	-L${FT_IO_DIR} -lft_io
LDFLAGS				+=	-L${FT_STRING_DIR} -lft_string

ifeq (${DEBUG}, 1)
	CFLAGS	+=	-g
	CFLAGS	+=	-DDEBUG=1
endif

#######################################
#                RULES                #
#######################################
${NAME}: ${OBJ} ${FT_IO_A} ${FT_STRING_A}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@${MKDIR} ${@D}
	${CC} ${CFLAGS} $< ${OUTPUT_OPTION}

${FT_IO_A} ${FT_STRING_A}:
	@${MAKE} ${@F} -C ${@D}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean: clean
	${MAKE} $@ -C ${FT_IO_DIR}
	${MAKE} $@ -C ${FT_STRING_DIR}

re: clean all

fre: fclean all

.PHONY: all clean fclean re fre

-include coffee.mk
-include norm.mk
-include valgrind.mk
