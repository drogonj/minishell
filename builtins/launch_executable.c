/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:48:49 by ngalzand          #+#    #+#             */
/*   Updated: 2023/03/06 15:27:49 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*make_buffer(t_cmd *cmd)
{
	char	*buffer;
	char	*buffer2;

	buffer2 = 0;
	buffer = ft_strdup(cmd->line[0]);
	if (!buffer)
		free_core(cmd->core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	if (cmd->line[0][0] == '~')
	{
		buffer = remove_char(&buffer, '~');
		buffer2 = ft_strjoin_msh(ft_getenv(cmd->core->env, "HOME"), buffer);
		free(buffer);
		if (!buffer2)
			free_core(cmd->core, ft_printf(2, "minishell: fatal error\n"), TRUE);
    return (buffer2);
	}
	return (buffer);
}

void	launch_executable(t_cmd *cmd)
{
	char	*buffer;

	if (!cmd->line[0] || !cmd->line[0][0])
		return ;
	buffer = make_buffer(cmd);
	if (execve(buffer, cmd->line, cmd->core->env) == -1)
	{
		set_error(cmd->core, errno,
			ft_printf(2, "minishell: %s: ", buffer));
		perror("");
	}
	else
		cmd->core->error = 0;
	free(buffer);
	free_core(cmd->core, 0, FALSE);
	exit(0);
}
