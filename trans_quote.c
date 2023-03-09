/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:52:15 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:44:36 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trans_dol(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return ;
	while (line[++i])
	{
		if (line[i] == 39)
		{
			while (line[++i] != 39)
			{
				if (!line[i])
					return ;
				if (line[i] == '$')
					line[i] = 26;
			}
		}
		if (line[i] == 34)
		{
			while (line[++i] != 34)
				if (!line[i])
					return ;
		}
	}
	return ;
}

void	trans_sub(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == 26)
			line[i] = '$';
		i++;
	}
	return ;
}

char	*trans_quote(char *line, int i, char *start)
{
	char	*new;

	start = line;
	if (!line)
		return (NULL);
	new = (char *)ft_calloc(sizeof(char), ft_strlen(line) + 1);
	while (line && *line && new)
	{
		if (*(line) && *(line) == 39)
		{
			while (*(++line) && *(line) != 39)
				new[i++] = *(line);
			if (*(line))
				line++;
		}
		if (*line && *(line) == 34)
		{
			while (*(++line) && *(line) != 34)
				new[i++] = *(line);
			if (*(line))
				line++;
		}
		if (*(line) && (*(line) != 39 || *(line) != 34))
			new[i++] = *(line++);
	}
	free(start);
	return (new);
}
