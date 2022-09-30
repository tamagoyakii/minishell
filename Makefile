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
			builtin_unset.c \
			path.c \
			pipe.c \
			redir.c \
			execute.c \
			heredoc.c \
			run_fork.c \
			init_execute.c \
			open.c
#PARSE_SRCS =

UTILS_SRCS = env1.c \
			env2.c \
			frees.c \
			global.c \
			signal.c

SRCS := ${addprefix ${EXECUTE_DIR}/, ${EXECUTE_SRCS}} \
		${addprefix ${UTILS_DIR}/, ${UTILS_SRCS}} \
		main_execute.c
libft = ./libs/libft/libft.a
#		${addprefix ${PARSE_DIR}/, ${PARSE_SRCS}} \#
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)

%.o : %.c
	cc $(CFLAGS) -c -o $@ $< -I $(INCLUDES)

$(NAME) : $(OBJS)
	make -C ./libs/libft
	cc $(CFLAGS) -o $@ $^ $(libft) -lreadline

clean :
	make -C ./libs/libft clean
	rm -f $(OBJS)

fclean : clean
	make -C ./libs/libft fclean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : clean fclean re all