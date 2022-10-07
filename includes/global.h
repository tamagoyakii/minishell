#ifndef GLOBAL_H
# define GLOBAL_H

# include "../libs/libft/libft.h"
# include <stdio.h>

typedef enum e_return_type
{
	SUCCESS,
	FAIL,
	TRUE = 1,
	FALSE = 0
}	t_return_type;

typedef enum e_token_type
{
	NONE,
	WORD,
	REDIR,
	PIPE
}	t_token_type;

typedef enum e_redir_type
{
	T_OUT = 1,
	A_OUT,
	IN,
	HDOC
}	t_redir_type;

typedef enum e_dummy_type
{
	CHAR	= 0x0001,
	_QUOTE	= 0x0002,
	S_QUOTE	= 0x0004,
	D_QUOTE	= 0x0008,
	_REDIR	= 0x0010,
	R_REDIR	= 0x0020,
	L_REDIR	= 0x0040,
	_PIPE	= 0x0100,
	SPACE	= 0x0200,
	BREAK	= 0x1000,
	ADD_NULL= 0x2000
}	t_dummy_type;

typedef enum e_error_type
{
	E_DUMMIES	= 0x01,
	E_TOKENS	= 0x02,
	E_ARGVS		= 0x04,
	E_SYNTAX	= 0x08
}	t_error_type;

typedef struct s_cmd
{
	int				cnt;
	struct s_list	*cmds;
}	t_cmd;

typedef struct s_type
{
	int	last;
	int	redir;
}	t_type;

typedef struct s_parse
{
	char			*line;
	char			*input;
	struct s_list	*dummys;
	struct s_list	*tokens;
	struct s_cmd	*cmd;
	struct s_type	*type;
}	t_parse;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

typedef struct s_dummy_info
{
	int		type;
	int		size;
	char	*addr;
}	t_dummy_info;

typedef struct s_dummy
{
	int		type;
	char	*value;
}	t_dummy;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*value;
	struct s_redir	*next;
}	t_redir;

typedef struct s_argv
{
	char			**cmd;
	struct s_redir	*in;
	struct s_redir	*out;
	struct s_redir	*hdoc;
	struct s_argv	*next;
}	t_argv;

typedef struct s_info
{
	struct s_env	*env_list;
	char			**env;
	int				last_exit_num;
	pid_t			pid;
}	t_info;

extern t_info	g_info;

#endif
