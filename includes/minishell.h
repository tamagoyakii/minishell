/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:53:54 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/22 17:16:48 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE
}	t_token_type;

typedef enum e_redir_type
{
	T_OUT,
	A_OUT,
	INPUT,
	HEREDOC
}	t_redir_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int		t_type;
	char	*str;
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
	struct s_redir	*heredoc;
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
