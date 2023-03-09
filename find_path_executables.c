/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:55:41 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/03 13:43:05 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_var(char **s1, char **s2)
{
	if (*s1)
		free(*s1);
	*s1 = 0;
	if (s2 && *s2)
		free(*s2);
	if (s2)
		*s2 = 0;
	return (0);
}

static char	*check_executable(char *temp, char *command)
{
	char	*full_path;

	full_path = ft_strjoin(temp, command);
	if (!access(full_path, X_OK))
		return (full_path);
	reset_var(&full_path, 0);
	return (NULL);
}

static char	*search_executable(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	full_path = check_executable(temp, command);
	reset_var(&temp, 0);
	return (full_path);
}

char	*find_path_executable(char **env, char *command)
{
	char	*path_env;
	char	*path_cpy;
	char	*dir;
	char	*next;
	char	*found_path;

	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (0);
	path_cpy = ft_strdup(path_env);
	dir = path_cpy;
	while (dir)
	{
		next = ft_strchr(dir, ':');
		if (next)
			*(next++) = '\0';
		found_path = search_executable(dir, command);
		if (found_path)
			return (reset_var(&path_cpy, &path_env), found_path);
		dir = next;
	}
	reset_var(&path_cpy, &path_env);
	return (0);
}
