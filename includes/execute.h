#ifndef EXECUTE_H
# define EXCUTE_H

void	execute(t_argv *argv, t_env **env);
/* builtin */
void	single_builtin(t_argv *argv, t_env **env);
/* pipe */
void	set_stdout_pipe(t_argv *argv, t_pipe pipe, int num);
void	set_stdin_pipe(t_pipe pipe, int num);
void	close_pipe(t_pipe pipe, int size);
/* redir */
int		set_stdin_redir(t_argv *argv);
int		set_stdout_redir(t_argv *argv);
/* heredoc */
int		make_heredoc(t_argv *argv);
/* child */
void	child_process(t_argv *argv, t_pipe pipe, int i, t_env **env);


#endif