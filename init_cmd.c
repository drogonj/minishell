/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:41:46 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/13 18:25:19 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_struct(t_core *core)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fdi = 0;
	cmd->fdo = 1;
	cmd->line = core->cmd;
	cmd->opt = 0;
	cmd->function = 0;
	cmd->redirection = 0;
	cmd->core = core;
	return (cmd);
}

void	is_builtin(char *s, t_cmd *cmd)
{
	if (!s)
		return ;
	remake_underscore_env_var(cmd, FALSE);
	if (ft_strncmp(s, "echo", 5) == 0)
		cmd->function = &builtin_echo;
	if (ft_strncmp(s, "cd", 3) == 0)
		cmd->function = &builtin_cd;
	if (ft_strncmp(s, "pwd", 4) == 0)
		cmd->function = &builtin_pwd;
	if (ft_strncmp(s, "export", 7) == 0)
		cmd->function = &builtin_export;
	if (ft_strncmp(s, "unset", 6) == 0)
		cmd->function = &builtin_unset;
	if (ft_strncmp(s, "env", 4) == 0)
		cmd->function = &builtin_env;
	if (ft_strncmp(s, "exit", 5) == 0)
		cmd->function = &builtin_exit;
}

int	ext_command(t_core *core, t_cmd *cmd)
{
	char	*path_cmd;

	path_cmd = 0;
	if (cmd->line[0] == NULL)
		exit(1);
	if (cmd->line[0][0] == '\0')
		exit(1);
	path_cmd = find_path_executable(core->env, cmd->line[0]);
	if (!path_cmd)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->line[0]);
		exit(-1);
	}
	else if (execve(path_cmd, cmd->line, core->env) == -1)
		ft_printf(2, "minishell: Error\n");
	if (path_cmd)
		free(path_cmd);
	free_core(core, 0, FALSE);
	exit(1);
}

t_cmd	*init_cmd(t_core *core, t_cmd *cmd)
{
	if (!core->cmd || !core->cmd[0])
		return (cmd);
	cmd = init_struct(core);
	if (!cmd)
		free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	is_builtin(core->cmd[0], cmd);
	if (cmd->function)
		(cmd->function)(cmd);
	else if (contain_char(cmd->line[0], '/') != -1)
		launch_executable(cmd);
	return (cmd);
}

void	launch_cmd(t_core *core, t_cmd **cmd)
{
	int	i;
	int	count;

	johnny(TRUE, TRUE);
	count = count_pipe(cmd);
	i = 0;
	if (count == 1 && cmd[i]->function)
		(cmd[i]->function)(cmd[i]);
	else if (count == 1)
	{
		remake_underscore_env_var(cmd[i], FALSE);
		set_fork(cmd[i + 1], cmd[i], cmd[i]->fdi, cmd[i]->fdo);
		if (cmd[i]->fdi > 1)
			close(cmd[i]->fdi);
		if (cmd[i++]->fdo > 1)
			close(cmd[i - 1]->fdo);
	}
	else
		i = launch_multi_cmd(core, cmd);
	while (--i >= 0)
	{
		waitpid(cmd[i]->pid, &core->error, 0);
		core->error = core->error;
	}
	johnny(TRUE, FALSE);
}
