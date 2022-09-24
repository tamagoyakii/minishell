#ifndef PARSE_H
# define PARSE_H

/* jihyukim */
/* create_tokens.c */
int		is_pipe(char *input);
int		is_redir(char *chunk);
void	put_type(t_type *tokens, char *content);
int		create_tokens(t_chunk *chunk, t_type *tokens);
int		parse_tokens(t_argv *argvs, t_chunk *chunk);

/* create_argvs.c */
int		put_cmd(t_cmd *cmd, char **arr);
int		add_redir(t_argv *argvs, char *value, int r_type, int *last_type);
int		add_pipe(t_argv *argvs, t_cmd *cmd, int *last_type);
int		add_word(t_argv *argvs, t_list *cmds, char *value, int *last_type);
int		create_argv(t_argv *argvs, t_type *tokens);

/* token_utils.c */
t_type	*add_type(t_type *prev, int type, char *value);
t_argv	*add_argv(t_argv *prev);

#endif