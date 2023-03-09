/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:41:23 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/14 17:23:32 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long int	ft_strlen_varname(char *str)
{
	long int	i;

	i = 0;
	if (!str)
		return (0);
	if (contain_char(str, '=') == -1)
		return (ft_strlen(str));
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*ft_getenv(char **env, char *var)
{
	int		i;
	int		j;
	int		k;
	char	*content;

	i = 0;
	while (env[i] && ft_strncmp(env[i], var, ft_strlen_varname(env[i])) != 0)
		i++;
	if (!env[i])
		return (0);
	content = ft_calloc(ft_strlen(env[i]) - ft_strlen_varname(env[i]), 1);
	if (!content)
		return (0);
	k = -1;
	j = ft_strlen_varname(env[i]);
	while (env[i][j])
		content[++k] = env[i][++j];
	return (content);
}

void	add_mnsh_history(t_core *core, char **line)
{
	if (!line || !*line)
		return ;
	if (!*line[0])
		return ;
	add_history(*line);
	if (write(core->history_fd, *line, ft_strlen(*line)) == -1)
	{
		free(line);
		line = 0;
		free_core(core, ft_printf(2, "minishell: unistd: write failure.\n"), 1);
	}
	if (write(core->history_fd, "\n", 1) == -1)
	{
		if (line)
		{
			free(line);
			line = 0;
		}
		free_core(core, ft_printf(2, "minishell: unistd: write failure.\n"), 1);
	}
}

int	set_error(t_core *core, int error, int function)
{
	(void)function;
	if (!core)
		return (-1);
	core->error = error;
	return (error);
}
