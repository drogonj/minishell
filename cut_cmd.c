/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 19:23:52 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:54:09 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_cmd(t_cmd *cmd, char **line)
{
	int		i;
	char	**new;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == '|')
			break ;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (*line)
	{
		if ((*line)[0] == '|')
			break ;
		new[i++] = ft_strdup(*(line++));
	}
	new[i] = NULL;
	cmd->line = new;
	return (++line);
}

void	set_last(t_core *core, t_cmd *cmd)
{
	char	*var;

	trans_dol(cmd->olast);
	cmd->olast = trans_quote(cmd->olast, 0, NULL);
	var = search_var(cmd->olast);
	if (var)
	{
		cmd->olast = replace_variable(core, var, cmd->olast);
		free(var);
	}
	trans_sub(cmd->olast);
	trans_dol(cmd->ilast);
	cmd->ilast = trans_quote(cmd->ilast, 0, NULL);
	var = search_var(cmd->ilast);
	if (var)
	{
		cmd->ilast = replace_variable(core, var, cmd->ilast);
		free(var);
	}
	trans_sub(cmd->ilast);
	(void)core;
}

void	set_variable(t_core *core, t_cmd *cmd)
{
	set_last(core, cmd);
	modify_line(core, cmd->line);
	modify_line(core, cmd->fdi1);
	modify_line(core, cmd->fdi2);
	modify_line(core, cmd->fdo1);
	modify_line(core, cmd->fdo2);
}

void	set_cmd(t_core *core, char **line)
{
	int		i;
	t_cmd	**cmd;

	i = -1;
	cmd = core->cmd_village;
	while (core->cmd_village[++i])
	{
		line = copy_cmd(core->cmd_village[i], line);
		core->cmd_village[i]->fdi1 = locate_fdi1(core->cmd_village[i]->line);
		core->cmd_village[i]->fdo1 = locate_fdo1(core->cmd_village[i]->line);
		core->cmd_village[i]->fdi2 = locate_fdi2(core->cmd_village[i]->line);
		core->cmd_village[i]->fdo2 = locate_fdo2(core->cmd_village[i]->line);
		core->cmd_village[i]->olast = loc_last(core->cmd_village[i]->line, '>');
		core->cmd_village[i]->ilast = loc_last(core->cmd_village[i]->line, '<');
		del_fdi(core->cmd_village[i]->line, 0, 0);
		set_variable(core, core->cmd_village[i]);
		core->cmd_village[i]->fdi = 0;
		core->cmd_village[i]->fdo = 1;
		core->cmd_village[i]->function = 0;
		core->cmd_village[i]->redirection = 0;
		core->cmd_village[i]->core = core;
		is_builtin(core->cmd_village[i]->line[0], core->cmd_village[i]);
		open_fdo(cmd[i]->fdo1, cmd[i]->fdo2, cmd[i], 0);
		open_fdi(cmd[i]->fdi1, cmd[i]->fdi2, cmd[i], 0);
	}
}

void	init_t_cmd(t_core *core, char **line)
{
	t_cmd	**cmdv;
	int		i;

	i = 1;
	core->error = matrix(2, core->error);
	while (*line)
		if ((*(line++))[0] == '|')
			i++;
	cmdv = malloc(sizeof(t_cmd *) * (i + 1));
	cmdv[i] = NULL;
	while (--i != -1)
		cmdv[i] = malloc(sizeof(t_cmd));
	core->cmd_village = cmdv;
	set_cmd(core, core->cmd);
}
