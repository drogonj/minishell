/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:43:15 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/14 15:38:14 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_variable(char *line, char *var, int size)
{
	int		i;
	char	*new;
	char	*start;

	i = 0;
	start = line;
	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(var)));
	if (!new)
		return (0);
	while (*line != '$')
		new[i++] = *(line++);
	line += size + 1;
	if (var)
	{
		while (*var)
			new[i++] = *(var++);
	}
	while (*line)
		new[i++] = *(line++);
	new[i] = '\0';
	free(start);
	return (new);
}

char	*replace_variable_line(t_core *core, char *var, char *line)
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
			{
				loc++;
				if ((*loc != '\'' && *loc != '\"' && *loc != '\0'))
					return (cat_variable(line, loc, ft_strlen(var)));
				else
					return (line);
			}
		}
		i++;
	}
	return (line);
}

char	*check_variable_line(t_core *core)
{
	char	*var;

	if (!core->line)
		return (core->line);
	trans_dol(core->line);
	var = search_var(core->line);
	if (var)
	{
		if (var[0] != '\'' && var[0] != '\"')
		core->line = replace_variable_line(core, var, core->line);
		free(var);
	}
	trans_sub(core->line);
	return (core->line);
}
