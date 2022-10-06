#ifndef PARSE_H
# define PARSE_H

# include "./utils.h"

# define SHE 0	/* shell	*/
# define DFL 1	/* default	*/
# define IGN 2	/* ignore	*/

/* create_tokens.c */
int		is_pipe(char *input);
int		is_redir(char *chunk);
int		create_tokens(t_list *chunks, t_list **tokens);
/* create_argvs_2.c */
int		put_cmd(t_cmd *cmd, t_argv **argvs);
int		put_argv(t_argv **argvs, t_token *token, t_cmd *cmd, t_type *type);
/* create_argvs.c */
int		create_argvs(t_argv **argvs, t_list **tokens,
			t_cmd **cmd, t_type **type);
/* split_dummy.c */
int		search_dummy(t_dummy *dummy, char *line);
/* split_line.c */
int		split_line(t_list **chunks, t_list **dummys, char *line);
/* replace_env_2.c */
int		ft_keylen(char *str);
int		is_variable(char *input, int *flag);
/* replace_env.c */
int		replace_env(char **line, char *input);
/* parse.c */
void	parse(t_argv **argvs);

#endif
