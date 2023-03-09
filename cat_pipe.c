/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:03:54 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/13 13:11:55 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_pipe(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 0 && cmd[i - 1] && cmd[i - 1][0]
		&& cmd[i - 1][0] == '|')
		return (1);
	return (0);
}

char	*cat_pipe(t_core *core, char *line)
{
	char	*temp;

	temp = readline("pipe>");
	core->line = ft_strjoin(line, temp);
	free(line);
	free(temp);
	if (!core->line)
		fatal_error(core);
	return (core->line);
}

int	count_pipe(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}
