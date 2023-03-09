/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:09:33 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/14 17:08:23 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free_cmd(t_cmd *cmd)
{
	cmd->line = ft_free_tab(cmd->line);
	cmd->fdi1 = ft_free_tab(cmd->fdi1);
	cmd->fdi2 = ft_free_tab(cmd->fdi2);
	cmd->fdo1 = ft_free_tab(cmd->fdo1);
	cmd->fdo2 = ft_free_tab(cmd->fdo2);
	cmd->olast = ft_free(cmd->olast);
	cmd->ilast = ft_free(cmd->ilast);
	if (cmd->fdi != 0)
		close(cmd->fdi);
	if (cmd->fdo != 1)
		close(cmd->fdo);
	cmd = ft_free(cmd);
	return (NULL);
}

void	re_init_core(t_core *core)
{
	int	i;

	i = -1;
	if (core->line)
		core->line = ft_free(core->line);
	core->cmd = ft_free_tab(core->cmd);
	while (core->cmd_village[++i])
		core->cmd_village[i] = ft_free_cmd(core->cmd_village[i]);
	core->cmd_village = ft_free(core->cmd_village);
}

int	free_core(t_core *core, int function, t_bool must_exit)
{
	int	i;

	i = -1;
	(void)function;
	if (!core)
		return (0);
	close(core->history_fd);
	clear_history();
	if (core->cmd)
		core->cmd = ft_free_tab(core->cmd);
	if (core->env)
		core->env = ft_free_tab(core->env);
	if (core->cmd_village)
		while (core->cmd_village[++i])
			core->cmd_village[i] = ft_free_cmd(core->cmd_village[i]);
	core->cmd_village = ft_free(core->cmd_village);
	core->line = ft_free(core->line);
	core = ft_free(core);
	if (function && must_exit == TRUE)
		exit(EXIT_FAILURE);
	if (must_exit == TRUE)
		exit(EXIT_SUCCESS);
	return (0);
}

static int	exit_with_args(t_cmd *cmd, const int size)
{
	int			i;

	i = -1;
	while (cmd->line[1] && cmd->line[1][++i])
	{
		if (cmd->line[1][i] < '0' || cmd->line[1][i] > '9')
		{
			ft_printf(2, "minishell: exit: %s: numeric argument required\n",
				cmd->line[1]);
			free_core(cmd->core, 0, FALSE);
			return (255);
		}
	}
	if (size > 2)
	{
		ft_printf(1, "minishell: exit: too many arguments\n");
		cmd->core->error = 1;
		return (-1);
	}
	return (ft_atoi(cmd->line[1]));
}

void	builtin_exit(t_cmd *cmd)
{
	const int	size = tab_len(cmd->line);
	int			exit_val;

	ft_printf(1, "exit\n");
	if (size > 1)
	{
		exit_val = exit_with_args(cmd, size);
		if (exit_val != -1)
			exit(exit_val);
	}
	else
	{
		exit_val = cmd->core->error;
		free_core(cmd->core, 0, FALSE);
		exit(exit_val);
	}
}
