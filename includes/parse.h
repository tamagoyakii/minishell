#ifndef PARSE_H
# define PARSE_H

/* signal 탈취를 위한 매크로 상수 shell, default, ignore  */
# define SHE 0
# define DFL 1
# define IGN 2

# include "./minishell.h"

typedef enum e_quote
{
	NAQ = 1,
	QUOTE = 2,
	DQUOTE = 4
}	t_quote;

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

/* jihyukim */
/* create_tokens.c */
int		is_pipe(char *input);
int		is_redir(char *chunk);
void	free_token(void *token);
int		create_tokens(t_list *chunks, t_list **tokens);

/* create_argvs.c */
int		create_argvs(t_argv **argvs, t_list *tokens);

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

/* init_argvs.c */
int		init_argvs(t_argv **argvs, t_cmd **cmd, t_type **type);

/* donghyuk */
int		split_line(t_list **chunks, char *line);

void	parse(t_argv **argvs, t_env *env);

#endif
