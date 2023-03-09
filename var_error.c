/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:24:59 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:43:03 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error_var(t_core *core, char **cmd)
{
	int		i;
	char	*error;

	i = 0;
	error = ft_itoa(core->error);
	if (!cmd || !error)
		return ;
	while (cmd[i])
	{
		if (ft_strnstr(cmd[i], "$?", ft_strlen(cmd[i])) != NULL)
			cmd[i] = cat_variable(cmd[i], error, 1);
		i++;
	}
	free(error);
}
