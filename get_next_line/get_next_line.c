/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:49:14 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/14 12:12:52 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remake_temp(char *temp)
{
	char	*newtemp;
	size_t	i;
	size_t	j;

	newtemp = 0;
	i = 0;
	j = contain_char_gnl(temp) + 1;
	newtemp = (char *)ft_calloc_gnl((ft_strlen_gnl(temp) - j)
			+ 1, sizeof(char));
	if (!newtemp)
		return (ft_freetmp_gnl(&temp, 0, 0));
	while (temp[j])
	{
		newtemp[i] = temp[j];
		i++;
		j++;
	}
	ft_freetmp_gnl(&temp, 0, 0);
	return (newtemp);
}

char	*create_newline(char *temp)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!temp || temp[0] == 0)
		return (0);
	if (contain_char_gnl(temp) == -1)
		line = (char *)ft_calloc_gnl(ft_strlen_gnl(temp) + 1, sizeof(char));
	else
		line = (char *)ft_calloc_gnl(contain_char_gnl(temp) + 1, sizeof(char));
	if (!line)
		return (0);
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	return (line);
}

int	read_next_line(int fd, char **temp)
{
	char	*buffer;
	int		readval;

	readval = -1;
	buffer = (char *)ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (-1);
	readval = read(fd, buffer, BUFFER_SIZE);
	if (readval >= 0)
		*temp = ft_strjoin_gnl(*temp, buffer);
	free(buffer);
	return (readval);
}

char	*get_next_line(int fd)
{
	static char	*temp = 0;
	char		*line;
	int			readval;

	readval = -2;
	line = 0;
	while (!line && readval != 0 && readval != -1 && (fd >= 0 && fd <= 1024))
	{
		readval = read_next_line(fd, &temp);
		if (readval == -1)
			return (ft_freetmp_gnl(&temp, 0, 0));
		else if (readval == 0 || (readval >= 1 && contain_char_gnl(temp) >= 0))
		{
			line = create_newline(temp);
			if (!line)
				return (ft_freetmp_gnl(&temp, 0, 0));
			if (temp && contain_char_gnl(temp) >= 0)
				temp = remake_temp(temp);
			else if (readval == 0)
				ft_freetmp_gnl(&temp, 0, 0);
		}
	}
	return (line);
}
