#ifndef PARSE_H
# define PARSE_H

typedef struct s_cmd
{
	int		cnt;
	t_list	*cmds;
}	t_cmd;

typedef struct s_token
{
	int				type;
	char			*value;
}	t_token;

/* jihyukim */
/* create_tokens.c */
int		is_pipe(char *input);
int		is_redir(char *chunk);
int		create_tokens(t_list *chunks, t_list **tokens);

/* create_argvs.c */
int		create_argvs(t_argv *argvs, t_type *tokens);

/* utils_t_token.c */
t_token	*create_token(int type, char *value);
void	free_token(void *token);

/* utils_t_type.c */
t_type	*create_type(int type, char *value);
t_type	*ft_typelast(t_type *type);
void	ft_typeadd_back(t_type **types, t_type *new);

/* utils_t_argv.c */
t_argv	*create_argv(void);
t_argv	*ft_argvlast(t_argv *argv);
void	ft_argvadd_back(t_argv **argvs, t_argv *new);

/* utils_t_list.c */
void	free_lst_only(t_list *lists);

#endif