/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:59:57 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:42:39 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_var(char *line, int end)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * end + 1);
	if (!var)
		return (NULL);
	while (i < end)
	{
		var[i] = line[i];
		i++;
	}
	var[i] = '\0';
	if (i == 0)
	{
		free(var);
		return (NULL);
	}
	return (var);
}

char	*search_var(char *line)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i++] == '$')
		{
			while ((ft_isalnum(line[i + i2]) == 1
					|| line[i + i2] == '_') && line[i + i2])
				i2++;
			return (copy_var(line + i, i2));
		}
	}
	return (NULL);
}

char	*replace_variable(t_core *core, char *var, char *line)
{
	int		i;
	char	*loc;

	i = 0;
	while (core->env[i])
	{
		loc = ft_strnstr(core->env[i], var, ft_strlen(var) + 1);
		if (loc)
		{
			loc = loc + (ft_strlen(var));
			if (*loc == '=')
				return (cat_variable(line, loc + 1, ft_strlen(var)));
		}
		i++;
	}
	return (cat_variable(line, loc, ft_strlen(var)));
}

void	check_variable(t_core *core, char **cmd)
{
	int		i;
	char	*var;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		var = search_var(cmd[i]);
		if (var)
		{
			cmd[i] = replace_variable(core, var, cmd[i]);
			free(var);
		}
		i++;
	}
}
