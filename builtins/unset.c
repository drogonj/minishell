/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:47 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/14 15:59:49 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	invalid_check(t_cmd *cmd, int i)
{
	if (contain_invalid(cmd->line[i], 0) != -1)
	{
		set_error(cmd->core, 32,
			ft_printf(2, "minishell: unset: Invalid name\n"));
		return (1);
	}
	return (0);
}

void	builtin_unset(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	cmd->core->error = 0;
	while (cmd->line[++i])
	{
		j = -1;
		if (invalid_check(cmd, i))
			return ;
		while (cmd->core->env[++j])
		{
			if (ft_strncmp(cmd->core->env[j], cmd->line[i],
					ft_strlen_varname(cmd->core->env[j])) == 0)
			{
				free(cmd->core->env[j]);
				while (cmd->core->env[j + 1])
				{
					cmd->core->env[j] = cmd->core->env[j + 1];
					j++;
				}
				cmd->core->env[j] = 0;
			}
		}
	}
}
