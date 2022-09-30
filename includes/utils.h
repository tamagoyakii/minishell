#ifndef UTILS_H
# define UTILS_H

# include "./minishell.h"

/* global */
void	*ft_malloc(size_t size);
void	ft_error(char *cmd, char *msg, int err_num);
void	ft_error_exit(char *cmd, char *msg, int exit_num);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
void	free_strs(char **strs);
void	free_argv(t_argv *argv);

/* util_env */
int		is_valid_key(char *key);
char	*make_key(char *cmd);
t_env	*get_env(char *key);
t_env	*make_env(char *env);
void	add_env(t_env **lst, char *env);
void	print_invalid_key(char *cmd, char *input);
void	get_env_list_size(void);
void	init_env(char **env);
void	make_env_arr(void);

/* signal */
void	set_heredoc_signal(void);
void	set_child_signal(void);

#endif