#ifndef PARSE_H
# define PARSE_H

/* signal 탈취를 위한 매크로 상수 shell, default, ignore  */
# define SHE 0
# define DFL 1
# define IGN 2

# include "./minishell.h"

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
	E_CHUNKS	= 0x01,
	E_TOKENS	= 0x02,
	E_ARGVS		= 0x04,
	E_SYNTAX	= 0x08
}	t_error_type;

typedef struct s_parse
{
	t_list	*chunks;
	t_list	*tokens;
	t_cmd	*cmd;
	t_type	*type;
}	t_parse;

typedef struct s_cmd
{
	int		cnt;
	t_list	*cmds;
}	t_cmd;

typedef struct s_type
{
	int	last;
	int	redir;
}	t_type;

typedef struct s_token
{
	int				type;
	char			*value;
}	t_token;

typedef	struct s_dummy
{
	int		type;
	int		size;
	char	*addr;
}	t_dummy;


/* jihyukim */
/* create_tokens.c */
int		is_pipe(char *input);
int		is_redir(char *chunk);
void	free_token(void *token);
int		create_tokens(t_list *chunks, t_list **tokens);

/* create_argvs_2.c */
int		put_cmd(t_cmd *cmd, t_argv **argvs);
int		put_argv(t_argv **argvs, t_token *token, t_cmd *cmd, t_type *type);

/* create_argvs.c */
int		create_argvs(t_argv **argvs, t_parse *parse);

/* utils_t_redir.c */
t_redir	*create_redir(int redir, char *value);
t_redir	*ft_redirlast(t_redir *redir);
void	ft_rediradd_back(t_redir **redir, t_redir *new);

/* utils_t_argv.c */
t_argv	*create_argv(void);
t_argv	*ft_argvlast(t_argv *argv);
void	ft_argvadd_back(t_argv **argvs, t_argv *new);

/* utils_t_list.c */
void	free_lst_only(t_list **lists);
void	free_content(void *content);

/* donghyuk */
int	search_dummy(t_dummy *dummy, char *line);
int	split_line(t_list **chunks, char *line);

void	parse(t_argv **argvs);

#endif
