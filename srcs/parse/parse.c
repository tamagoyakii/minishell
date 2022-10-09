#include "../../includes/parse.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	error_handler(t_parse info, int err)
{
	free(info.line);
	if (!err)
	{
		ft_lstclear(&info.dummys, free_dummy);
		ft_lstclear(&info.tokens, free_content);
	}
	if (err & E_DUMMIES)
		ft_lstclear(&info.dummys, free_dummy);
	if (err & E_TOKENS)
		ft_lstclear(&info.tokens, free_token);
	if (err & E_SYNTAX)
		ft_error("syntax error", "unexpected tokens", SYNTEX_ERR);
	if (err & E_ARGVS)
	{
		ft_lstclear(&info.tokens, free_token);
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

static int	check_input(char *input)
{
	char	*seek;

	seek = input;
	if (!seek)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_info.last_exit_num);
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
		if (only_wspace(info.line))
			continue ;
		err = create_tokens(&info.tokens, &info.dummys, info.line);
		if (!err)
			err = create_argvs(argvs, &info.tokens, &info.cmd, &info.type);
		if (!error_handler(info, err))
			break ;
	}
}
