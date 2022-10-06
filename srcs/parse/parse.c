#include "../../includes/parse.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	error_handler(t_parse info, int err)
{
	ft_lstclear(&info.dummys, free_content);
	free(info.line);
	if (!err)
	{
		free_lst_only(&info.chunks);
		ft_lstclear(&info.tokens, free_content);
	}
	if (err & E_CHUNKS)
		ft_lstclear(&info.chunks, free_content);
	if (err & E_TOKENS)
		ft_lstclear(&info.tokens, free_content);
	if (err & E_SYNTAX)
		ft_error("syntax error", "", SYNTEX_ERR);
	if (err & E_ARGVS)
	{
		ft_lstclear(&info.tokens, free_content);
		if (info.cmd)
		{
			free_lst_only(&info.cmd->cmds);
			free(info.cmd);
		}
		if (info.type)
			free(info.type);
	}
	return (err);
}

static int	only_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (FALSE);
		line++;
	}
	return (TRUE);
}

static int	check_input(char *input)
{
	char	*seek;

	seek = input;
	if (!seek)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(SUCCESS);
	}
	if (!(*seek))
		return (FAIL);
	add_history(input);
	return (SUCCESS);
}

static int	rl_replace(t_parse *info)
{
	info->input = readline("minishell > ");
	if (check_input(info->input))
	{
		free(info->input);
		return (FAIL);
	}
	if (replace_env(&info->line, info->input))
	{
		free(info->input);
		return (FAIL);
	}
	free(info->input);
	return (SUCCESS);
}

void	parse(t_argv **argvs)
{
	t_parse	info;
	int		err;

	while (1)
	{
		ft_memset(&info, 0, sizeof(t_parse));
		if (rl_replace(&info))
			continue ;
		if (only_whitespace(info.line))
			continue ;
		err = split_line(&info.chunks, &info.dummys, info.line);
		if (!err)
			err = create_tokens(info.chunks, &info.tokens);
		if (!err)
			err = create_argvs(argvs, &info.tokens, &info.cmd, &info.type);
		if (!error_handler(info, err))
			break ;
	}
}
