#include "../../includes/parse.h"
#include <readline/readline.h>

/*
static void	test_argvs(t_argv **argvs)
{
	int	i = -1;
	int j = -1;
	while (*argvs)
	{
		++i;
		j = -1;
		while ((*argvs)->out)
		{
			printf("out_%d_%d: %d, %s\n", i, ++j, (*argvs)->out->type, (*argvs)->out->value);
			(*argvs)->out = (*argvs)->out->next;
		}
		j = -1;
		while ((*argvs)->in)
		{
			printf("in_%d_%d: %d, %s\n", i, ++j, (*argvs)->in->type, (*argvs)->in->value);
			(*argvs)->in = (*argvs)->in->next;
		}
		j = -1;
		while ((*argvs)->hdoc)
		{
			printf("hdoc_%d_%d: %d, %s\n", i, ++j, (*argvs)->hdoc->type, (*argvs)->hdoc->value);
			(*argvs)->hdoc = (*argvs)->hdoc->next;
		}
		j = -1;
		while ((*argvs)->cmd[++j])
			printf("cmd_%d_%d: %s\n", i, j, (*argvs)->cmd[j]);
		*argvs = (*argvs)->next;
	}
}
*/

/*
static void read_input(char **line)
{
	while(1)
	{
		*line = readline("minishell $ ");
		if (!*line)
			continue;
		if (*line != '\0')
			free(*line);
		add_history(line);
		if (!is_whitespace(line))
			continue;
	}
}
*/

static int	error_handler(t_parse info, int err)
{
	ft_lstclear(&info.dummys, free_content);
	free(info.line);
	if (!err)
		ft_lstclear(&info.tokens, free_content);
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

static void	init_info(t_parse *info)
{
	info->line = NULL;
	info->input = NULL;
	info->dummys = NULL;
	info->chunks = NULL;
	info->tokens = NULL;
	info->cmd = NULL;
	info->type = NULL;
}

int	check_input(char *input)
{
	char	*line;

	line = input;
	if (!line)
		exit (SUCCESS);
	while (*line == ' ')
		line++;
	if (*line != '\0')
		add_history(input);
	else
	{
		free(input);
		return (FAIL);
	}
	return (SUCCESS);
}

int	take_input(t_parse *info)
{
	info->input = readline("minishell > ");
	if (check_input(info->input))
		return (FAIL);
	info->line = replace_env(info->input);
	// replace_env에서는 에러 처리 안하는지?
	free(info->input);
	return (SUCCESS);
}

void	parse(t_argv **argvs)
{
	t_parse	info;
	int		err;

	while (1)
	{
		init_info(&info);
		if (take_input(&info))
			continue;
		err = split_line(&info.chunks, &info.dummys, info.line);
		if (!err)
			err = create_tokens(info.chunks, &info.tokens);
		if (!err)
			err = create_argvs(argvs, &info.tokens, &info.cmd, &info.type);
		if (!error_handler(info, err))
			break ;
	}
}
