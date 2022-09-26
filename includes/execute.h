#ifndef EXECUTE_H
# define EXCUTE_H

void	execute(t_argv *argv, t_env *env);
/* builtin */
void	single_builtin(t_argv *argv, t_env *env);
/* pipe */
void	set_stdout_pipe(t_argv *argv, int **pipe, int num);
void	set_stdin_pipe(int **pipe, int num);
void	close_pipe(int **pipes);
/* redir */
int		set_stdin_redir(t_argv *argv);
int		set_stdout_redir(t_argv *argv);
/* heredoc */
int		make_heredoc(t_argv *argv);
/* child */
void	child_process(t_argv *argv, t_env *env, int **pipe, int i);
/* signal */
void	set_heredoc_signal(void);
void	set_child_signal(void);
/* path */
char	*get_path(t_argv *argv, t_env *env);
/* util */
void	*ft_malloc(size_t size);
int		is_builtin(char *cmd);
int		ft_open(char *file, int type);

#endif