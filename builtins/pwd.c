/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:45 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/13 17:32:21 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(t_cmd *cmd)
{
	char	*buffer;
	t_bool	error;

	buffer = 0;
	error = FALSE;
	buffer = getcwd(buffer, 0);
	if (buffer)
	{
		if (ft_putstr_fd(buffer, cmd->fdo) == -1)
			error = TRUE;
		if (ft_putchar_fd('\n', cmd->fdo) == -1)
			error = TRUE;
		free(buffer);
	}
	if (error == TRUE)
		cmd->core->error = errno;
}
