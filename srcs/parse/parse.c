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

int	error_handler(t_parse p, int err)
{
	if (!err)
		return (NONE);
	if (err & E_CHUNKS)
		ft_lstclear(&p.chunks, free_content);
	if (err & E_TOKENS)
		ft_lstclear(&p.tokens, free_content);
	if (err & E_SYNTAX)
		ft_error("syntax error", "", SYNTEX_ERR);
	if (err & E_ARGVS)
	{
		ft_lstclear(&p.tokens, free_content);
		if (p.cmd)
		{
			free_lst_only(&p.cmd->cmds);
			free(p.cmd);
		}
		if (p.type)
			free(p.type);
	}
	return (FAIL);
}

void	init_parse(t_parse *p)
{
	p->line = 0;
	p->input = 0;
	p->chunks = 0;
	p->tokens = 0;
	p->cmd = 0;
	p->type = 0;
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

void	parse(t_argv **argvs)
{
	t_parse	p;
	char	*line;
	char	*input;
	int		err;

	while(1)
	{
		err = 0;
		init_parse(&p);
		input = readline("minishell > ");
		if (check_input(input))
			continue ;
		line = replace_env(input);
		free(input);
		if (!err)
		 	err = split_line(&p.chunks, line);
		free(line);
		if (!err)
			err = create_tokens(p.chunks, &p.tokens);
		if (!err)
		{
			free_lst_only(&p.chunks);
			err = create_argvs(argvs, &p);
		}
		if (!error_handler(p, err))
		{
			ft_lstclear(&p.tokens, free_content);
			break ;
		}
	}
}
