NAME = minishell

EXECUTE_DIR = ./srcs/execute
PARSE_DIR = ./srcs/parse
UTILS_DIR = ./srcs/utils
INCLUDES = ./includes
EXECUTE_SRCS = builtin.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c	\
			path.c \
			pipe.c \
			redir.c \
			execute.c \
			heredoc.c \
			run_fork.c \
			init_execute.c \
			open.c

#			replace.c
PARSE_SRCS = parse.c \
			split_dummy.c \
			split_line.c \
			create_tokens.c \
			create_argvs.c \
			create_argvs_2.c \
			utils_env.c \
			replace.c

UTILS_SRCS = alloc.c \
			env1.c \
			env2.c \
			error.c \
			signal.c \
			t_argv.c \
			t_list.c \
			t_redir.c

SRCS := ${addprefix ${EXECUTE_DIR}/, ${EXECUTE_SRCS}} \
		${addprefix ${PARSE_DIR}/, ${PARSE_SRCS}} \
		${addprefix ${UTILS_DIR}/, ${UTILS_SRCS}} \
		./srcs/main.c

libft = ./libs/libft/libft.a
#		${addprefix ${PARSE_DIR}/, ${PARSE_SRCS}} \#

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

all : $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c -o $@ $< -I $(INCLUDES)

$(NAME) : $(OBJS)
	@make -C ./libs/libft
	@cc $(CFLAGS) -o $@ $^ $(libft) -lreadline
	@echo "🙋‍♀️🙋‍♂️ make"
# @echo "💧⛽️🧼 make"

clean :
	@make -C ./libs/libft clean
	@rm -f $(OBJS)
	@echo "🙋‍♀️🙋‍♂️ clean"
# @echo "💧⛽️🧼 clean"

fclean : clean
	@make -C ./libs/libft fclean
	@rm -f $(NAME)
	@echo "🙋‍♀️🙋‍♂️ fclean"
# @echo "💧⛽️🧼 fclean"

re : fclean all

.PHONY : clean fclean re all
