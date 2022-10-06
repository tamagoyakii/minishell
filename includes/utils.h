#ifndef UTILS_H
# define UTILS_H

# include "./global.h"

# define ERR_IS_A_DIRECTORY 126
# define ERR_CMD_NOT_FOUND 127
# define ERR_EXIT_NAN 255
# define SYNTEX_ERR 258

/* alloc.c */
void	free_strs(char **strs);
void	*ft_malloc(size_t size);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
/* env.c */
int		is_valid_key(char *key);
char	*make_key(char *cmd);
t_env	*get_env(char *key);
t_env	*make_env(char *env);
void	add_env(t_env **lst, char *env);
void	print_invalid_key(char *cmd, char *input);
int		get_env_list_size(void);
void	init_env(char **env);
void	make_env_arr(void);
/* error.c */
void	ft_error(char *cmd, char *msg, int err_num);
void	ft_error_exit(char *cmd, char *msg, int exit_num);
/* signal.c */
void	hdoc_sigint_handler(int signo);
void	main_signal(void);
void	ignore_signal(void);
void	default_signal(void);
/* t_argv.c */
t_argv	*create_argv(void);
void	free_argv(t_argv *argv);
t_argv	*ft_argvlast(t_argv *argv);
void	ft_argvadd_back(t_argv **argvs, t_argv *new);
/* t_list.c */
void	free_lst_only(t_list **lst);
void	free_content(void *content);
/* t_redir.c */
t_redir	*create_redir(int redir, char *value);
void	free_redir(t_redir *redir);
t_redir	*ft_redirlast(t_redir *redir);
void	ft_rediradd_back(t_redir **redir, t_redir *new);
/* check.c*/
int	is_wspace(char c);
int	only_wspace(char *str);
#endif
