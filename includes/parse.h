#ifndef PARSE_H
# define PARSE_H

# include "./utils.h"

# define SHE 0	/* shell	*/
# define DFL 1	/* default	*/
# define IGN 2	/* ignore	*/

/* create_tokens_2.c */
int		is_pipe(char *value);
int		is_redir(char *value);
int		get_token_type(int type);
char	*get_token_value(t_list **dummies);
t_token	*create_token(int type, char *value);
/* create_tokens.c */
int		create_tokens(t_list **tokens, t_list **dummys, char *line);
/* create_argvs_2.c */
int		put_cmd(t_cmd *cmd, t_argv **argvs);
int		put_argv(t_argv **argvs, t_token *token, t_cmd *cmd, t_type *type);
/* create_argvs.c */
int		create_argvs(t_argv **argvs, t_list **tokens,
			t_cmd **cmd, t_type **type);
/* create_dummies.c */
int		search_dummy(t_dummy_info *dummy, char *line);
/* replace_env_2.c */
int		ft_keylen(char *str);
int		is_variable(char *input, int *flag);
/* replace_env.c */
int		replace_env(char **line, char *input);
int		replace_env_hdoc(char **line, char *input);
int		get_size(char *input);
char	*get_value(char *line);
int		ft_keylen(char *str);

/* parse.c */
void	parse(t_argv **argvs);

#endif
