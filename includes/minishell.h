/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:53:54 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/23 17:55:35 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "./execute.h"

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
typedef struct s_token
{
	int				t_type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				r_type;
	char			*value;
	struct s_redir	*next;
}	t_redir;

/* 구현부로 넘김 */
typedef struct s_argv
{
	char			**cmd;
	struct s_redir	*in;
	struct s_redir	*out;
	struct s_redir	*hdoc;
	struct s_argv	*next;
}	t_argv;

typedef struct	s_pipe
{
	int		cnt;
	int		**pipe;
}	t_pipe;

typedef struct	s_error
{
	int		errno;
	int		last_errno;
	char	*msg;
}	t_error; // 에러 구현시 쓸 구조체, 수정 예정

extern t_error	g_error;

#endif
