/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:53:54 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/24 18:09:52 by jihyukim         ###   ########.fr       */
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

typedef enum e_return_type
{
	SUCCESS,
	FAIL
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

typedef struct s_chunk
{
	int		cnt;
	t_list	*chunks;
}	t_chunk;

typedef struct s_cmd
{
	int		cnt;
	t_list	*cmds;
}	t_cmd;

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

typedef struct s_pipe
{
	int		cnt;
	int		**pipe;
}	t_pipe;

typedef struct s_error
{
	int		errno;
	int		last_errno;
	char	*msg;
}	t_error; // 에러 구현시 쓸 구조체, 수정 예정

extern t_error	g_error;

#endif
