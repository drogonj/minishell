/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:07:07 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/14 15:38:12 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_block(t_core *core, char *line)
{
	char	**cmd;
	int		i;

	cmd = splitline(line, ' ');
	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (check_quote(cmd[i++]) == 1)
		{
			ft_free_tab(cmd);
			return (ft_printf(2, "minishell: quote is not closing\n"));
		}
	}
	core->cmd = cmd;
	return (0);
}

int	modify_line(t_core *core, char **cmd)
{
	int	i;

	i = 0;
	(void)core;
	if (cmd == NULL)
		return (0);
	while (cmd[i])
	{
		trans_dol(cmd[i]);
		cmd[i] = trans_quote(cmd[i], 0, NULL);
		i++;
	}
	i = 0;
	check_variable(core, cmd);
	check_error_var(core, cmd);
	while (cmd[i])
		trans_sub(cmd[i++]);
	return (0);
}

int	check_pipe(char **cmd)
{
	int	i;
	int	countpipe;

	i = 0;
	countpipe = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
			countpipe++;
		if (cmd[i][0] != '|')
			countpipe = 0;
		if (countpipe > 1 || cmd[0][0] == '|')
		{
			printf("minishell: parse error near '|'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_fd(char **cmd, int i, int fdi)
{
	while (cmd[++i])
	{
		if (cmd[i + 1])
		{
			if ((cmd[i][0] == '<' || cmd[i][0] == '>') && cmd[i + 1][0] == '|')
			{
				printf("minishell: parse erro near '|'\n");
				return (1);
			}
		}
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
			fdi++;
		if (cmd[i][0] != '<' && cmd[i][0] != '>')
			fdi = 0;
		if (fdi > 1 || (cmd[i + 1] == NULL && (cmd[i][0] == '<'
				|| cmd[i][0] == '>')))
		{
			printf("minishell: parse erro near '%s'\n", cmd[i - 1]);
			return (1);
		}
	}
	return (0);
}

int	pars_line(t_core *core, char *line)
{
	if (line == NULL)
	{
		core->line = NULL;
		printf("exit\n");
		free_core(core, 0, TRUE);
	}
	core->line = check_variable_line(core);
	if (core->line[0] == '\0')
		return (1);
	if (set_block(core, core->line) != 0)
		return (1);
	if (check_pipe(core->cmd) != 0 || check_fd(core->cmd, -1, 0) != 0)
	{
		core->line = ft_free(core->line);
		ft_free_tab(core->cmd);
		return (1);
	}
	if (check_end_pipe(core->cmd) == 1)
	{
		core->line = ft_free(core->line);
		ft_free_tab(core->cmd);
		return (pars_line(core, cat_pipe(core, core->line)));
	}
	return (0);
}
