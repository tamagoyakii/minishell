#ifndef EXECUTE_H
# define EXECUTE_H

# define ERR_CMD_NOT_FOUND 127
# define ERR_EXIT_NAN 255

# include "./minishell.h"

void	execute(t_argv *argv);

/* builtin */
void	single_builtin(t_argv *argv);

/* pipe */
void	set_stdout_pipe(t_argv *argv, int **pipe, int num);
void	set_stdin_pipe(int **pipe, int num);
void	close_pipe(int **pipes);

/* redir */
int		set_stdin_redir(t_argv *argv);
int		set_stdout_redir(t_argv *argv);

/* heredoc */
int		make_heredoc(t_argv *argv);
void	unlink_heredoc(t_argv *argv);

/* child */
void	child_process(t_argv *argv, int **pipe, int i);
void	child_command(t_argv *argv, pid_t *pids, int **pipes, int cnt_pipe);

/* signal */
void	set_heredoc_signal(void);
void	set_child_signal(void);

/* path */
char	*get_path(t_argv *argv);

/* util */
void	*ft_malloc(size_t size);
int		is_builtin(char **cmd);
int		ft_open(char *file, int type);
void	ft_error(char *cmd, char *msg, int err_num);
void	ft_error_exit(char *cmd, char *msg, int exit_num);

#endif
