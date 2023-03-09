/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:38 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/30 11:49:54 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_empty(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (1);
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != 0)
		return (0);
	return (1);
}

void	builtin_env(t_cmd *cmd)
{
	int		i;

	i = -1;
	cmd->core->error = 0;
	while (cmd->core->env[++i])
	{
		if (!is_empty(cmd->core->env[i]))
		{
			if (ft_putstr_fd(cmd->core->env[i], cmd->fdo) == -1)
				cmd->core->error = 1;
			if (ft_putchar_fd('\n', cmd->fdo) == -1)
				cmd->core->error = 1;
		}
	}
}
