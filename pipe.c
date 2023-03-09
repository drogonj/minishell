/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:28:08 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:49:14 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fork(t_cmd *next, t_cmd *cmd, int fdi, int fdo)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (next)
			close(next->fdi);
		dup2(fdi, 0);
		dup2(fdo, 1);
		if (cmd->function)
		{
			(cmd->function)(cmd);
			free_core(cmd->core, 0, FALSE);
			exit(0);
		}
		else if (contain_char(cmd->line[0], '/') != -1)
			launch_executable(cmd);
		else
			ext_command(cmd->core, cmd);
		exit(1);
	}
	return (0);
}

void	set_pipe_cmd(t_cmd **cmd, int i)
{
	int	p[2];

	if (cmd[i + 1])
	{
		pipe(p);
		if (cmd[i]->fdo > 1)
			close(p[1]);
		else
			cmd[i]->fdo = p[1];
		if (cmd[i + 1]->fdi > 1)
			close(p[0]);
		else
			cmd[i + 1]->fdi = p[0];
	}
}

int	launch_multi_cmd(t_core *core, t_cmd **cmd)
{
	int	i;

	i = 0;
	remake_underscore_env_var(cmd[i], TRUE);
	while (cmd[i])
	{
		set_pipe_cmd(cmd, i);
		set_fork(cmd[i + 1], cmd[i], cmd[i]->fdi, cmd[i]->fdo);
		if (cmd[i]->fdi > 0)
			close(cmd[i]->fdi);
		if (cmd[i]->fdo > 1)
			close(cmd[i]->fdo);
		i++;
	}
	(void)core;
	return (i);
}

void	loop_heredoc(char *end, int p, int w)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	while (1)
	{
		line = readline("heredoc>");
		if (ft_strncmp(line, end, ft_strlen(end) + ft_strlen(line)) == 0
			|| line == NULL)
			break ;
		if (w == 1)
			if (ft_putstr_fd(line, p) == 0 && ft_putstr_fd("\n", p) == 0)
				free(line);
		if (w == 0)
			free(line);
	}
	if (w == 1)
		close(p);
	free(line);
}
