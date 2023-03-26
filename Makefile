# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 12:46:31 by mcourtoi          #+#    #+#              #
#    Updated: 2023/03/26 06:47:14 by jodufour         ###   ########.fr        #
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
SRC					=							\
	${addprefix builtin/,						\
		${addprefix cd/,						\
			canonicalize.c						\
			core.c								\
			raw_curpath.c						\
		}										\
		${addprefix echo/,						\
			core.c								\
		}										\
		${addprefix env/,						\
			core.c								\
		}										\
		${addprefix exit/,						\
			core.c								\
		}										\
		${addprefix export/,					\
			core.c								\
			process_one.c						\
			surprise.c							\
		}										\
		${addprefix pwd/,						\
			core.c								\
		}										\
		${addprefix unset/,						\
			core.c								\
		}										\
	}											\
	${addprefix env/,							\
		${addprefix env_lst/,					\
			env_lst_add_back.c					\
			env_lst_add_front.c					\
			env_lst_clear.c						\
			env_lst_del_one.c					\
			env_lst_get_one.c					\
			env_lst_print_assigned.c			\
			env_lst_push_back.c					\
			env_lst_push_front.c				\
			env_new.c							\
		}										\
	}											\
	${addprefix exec/,							\
		${addprefix pid/,						\
			${addprefix lst/,					\
				pid_lst_add_back.c				\
				pid_lst_add_front.c				\
				pid_lst_clear.c					\
				pid_lst_del_one.c				\
				pid_lst_kill.c					\
				pid_lst_push_back.c				\
				pid_lst_push_front.c			\
				pid_lst_wait.c					\
				pid_new.c						\
			}									\
		}										\
		core.c									\
		redirections.c							\
		run.c									\
	}											\
	${addprefix here_doc/,						\
		here_doc.c								\
		here_tokens.c							\
	}											\
	${addprefix tokens/,						\
		${addprefix lst_tokens/,				\
			token_lst_add_back.c				\
			token_lst_add_front.c 				\
			token_lst_clear.c					\
			token_lst_del_one.c					\
			token_lst_del_range.c				\
			token_lst_find_first_by_type.c		\
			token_lst_is_first_builtin.c		\
			token_lst_push_back.c				\
			token_lst_push_front.c				\
			token_new.c							\
		}										\
		expand_tokens.c							\
		get_tokens.c							\
		tokens_operators.c						\
		tokens_utils.c							\
		classify_tokens.c						\
		classify_tokens_utils.c					\
	}											\
	${addprefix util/,							\
		${addprefix error/,						\
			command_not_found_error.c			\
			home_not_set_error.c				\
			internal_error.c					\
			invalid_option_error.c				\
			no_such_file_or_directory_error.c	\
			too_many_arguments_error.c			\
			usage_error.c						\
		}										\
		is_directory.c							\
	}											\
	main.c										\
	prompt.c									\
	signals.c

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
