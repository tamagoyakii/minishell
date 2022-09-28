/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:53:54 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/26 18:34:24 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "./execute.h"
# include "./parse.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <term.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>

typedef enum e_return_type
{
	SUCCESS,
	FAIL,
	TRUE = 1,
	FALSE = 0
}	t_return_type;

typedef enum e_token_type
{
	NONE,
	WORD,
	REDIR,
	PIPE
}	t_token_type;

typedef enum e_redir_type
{
	NONE,
	T_OUT,
	A_OUT,
	IN,
	HDOC
}	t_redir_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_type
{
	int				type;
	char			*value;
	struct s_type	*next;
}	t_type;

/* 구현부로 넘김 */
typedef struct s_argv
{
	char			**cmd;
	struct s_type	*in;
	struct s_type	*out;
	struct s_type	*hdoc;
	struct s_argv	*next;
}	t_argv;

typedef struct s_info
{
	struct s_env	*env_list;
	char			**env;
	int				last_exit_num;
	pid_t			pid;
}	t_info;

extern t_info	g_info;

#endif
