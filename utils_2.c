/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:00:59 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/09 09:14:32 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contain_var(char **env, char *var, int n)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, n) == 0)
			return (i);
	}
	return (-1);
}

static int	is_excluded(char c, char *excludes)
{
	int	i;

	i = -1;
	if (!excludes)
		return (0);
	if (!excludes[0])
		return (0);
	while (excludes[++i])
		if (excludes[i] == c)
			return (1);
	return (1);
}

int	contain_invalid(char *s, char *excludes)
{
	int	i;
	int	plus_count;

	i = -1;
	plus_count = 0;
	if (!s)
		return (0);
	while (s[++i] && s[i] != '=')
		if (s[i] == '+')
			plus_count++;
	i = -1;
	while (s[++i])
		if ((s[i] == '$' || s[i] == ';' || s[i] == '&' || s[i] == '<'
				|| s[i] == '>' || s[i] == '(' || s[i] == ')' || s[i] == '|'
				|| s[i] == '^' || s[i] == '!' || s[i] == '\\' || s[i] == '\"'
				|| s[i] == '\'' || s[i] == '`' || s[i] == '+' || s[i] == '-'
				|| s[i] == '.' || s[i] == '*' || s[i] == '?' || s[i] == '['
				|| s[i] == ']' || s[i] == '{' || s[i] == '}' || s[i] == '~'
				|| s[i] == ':' || s[i] == '=' || s[i] == ',' || s[i] == '%'
				|| s[i] == '#' || s[i] == '@' || s[i] == '!' || s[i] == '/')
			&& (!is_excluded(s[i], excludes)))
			return (i);
	if (plus_count > 1)
		return (0);
	return (-1);
}

char	*remove_char(char **s, char c)
{
	int		i;
	int		j;
	int		count;
	char	*newptr;

	if (!*s || !(*s)[0])
		return (0);
	if (!c)
		return (*s);
	i = -1;
	count = 0;
	while ((*s)[++i])
		if ((*s)[i] == c)
			count++;
	newptr = (char *)ft_calloc((ft_strlen(*s) - count) + 1, sizeof(char));
	if (!newptr)
		return (*s);
	j = -1;
	i = -1;
	while ((*s)[++i])
		if ((*s)[i] != c)
			newptr[++j] = (*s)[i];
	free(*s);
	return (newptr);
}

int	export_contain_plus(t_cmd *cmd, int *plus, int i)
{
	int	j;
	int	plus_count;

	j = -1;
	*plus = 0;
	plus_count = 0;
	while (cmd->line[i][++j] && cmd->line[i][j] != '=')
		if (cmd->line[i][j] == '+')
			plus_count++;
	if (ft_strnstr(cmd->line[i], "+=", ft_strlen(cmd->line[i])))
		*plus = 1;
	if (plus_count > 1)
		return (0);
	return (*plus);
}
