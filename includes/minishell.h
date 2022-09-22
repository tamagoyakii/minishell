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

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE
}	t_token_type;

typedef enum e_redir_type
{
	INPUT,
	OUTPUT,
	A_OUTPUT,
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
	struct s_argv	*next;
}	t_argv;

#endif
