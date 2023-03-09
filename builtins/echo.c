/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:35 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/30 11:49:53 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->line[i], "-n", 2) == 0)
		while (ft_strncmp(cmd->line[i], "-n", 2) == 0)
			i++;
	while (cmd->line[i])
	{
		if (ft_putstr_fd(cmd->line[i], cmd->fdo) == -1)
			cmd->core->error = 1;
		else
			cmd->core->error = 0;
		if (cmd->line[i + 1] != 0 && cmd->line[i][0])
			ft_putchar_fd(' ', cmd->fdo);
		i++;
	}
	if (cmd->line[1] && ft_strncmp(cmd->line[1], "-n", 2) == 0)
		;
	else
	{
		if (ft_putchar_fd('\n', cmd->fdo) == -1)
			cmd->core->error = 1;
		else
			cmd->core->error = 0;
	}
}
