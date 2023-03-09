/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:49:29 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/13 17:15:25 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**locate_fdi2(char **argv)
{
	int		i;
	int		count;
	char	**fd;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (argv[i++][0] == '<')
			if (argv[i -1][1] == '<')
				if (argv[i] != NULL)
					count++;
	}
	i = 0;
	fd = malloc(sizeof(char *) * (count + 1));
	while (*argv != NULL)
	{
		if ((*(argv++))[0] == '<')
			if ((*(argv -1))[1] == '<')
				if (*(argv) != NULL)
					fd[i++] = ft_strdup(*(argv));
	}
	fd[i] = NULL;
	return (fd);
}

char	**locate_fdo2(char **argv)
{
	int		i;
	int		count;
	char	**fd;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (argv[i++][0] == '>')
			if (argv[i - 1][1] == '>')
				if (argv[i] != NULL)
					count++;
	}
	i = 0;
	fd = malloc(sizeof(char *) * (count + 1));
	while (*argv != NULL)
	{
		if ((*(argv++))[0] == '>')
			if ((*(argv - 1))[1] == '>')
				if (*(argv) != NULL)
					fd[i++] = ft_strdup(*(argv));
	}
	fd[i] = NULL;
	return (fd);
}

char	**locate_fdi1(char **argv)
{
	int		i;
	int		count;
	char	**fd;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (argv[i++][0] == '<')
			if (argv[i -1][1] == '\0')
				if (argv[i] != NULL)
					count++;
	}
	i = 0;
	fd = malloc(sizeof(char *) * (count + 1));
	while (*argv != NULL)
	{
		if ((*(argv++))[0] == '<')
			if ((*(argv - 1))[1] == '\0')
				if (*(argv) != NULL)
					fd[i++] = ft_strdup(*(argv));
	}
	fd[i] = NULL;
	return (fd);
}

char	**locate_fdo1(char **argv)
{
	int		i;
	int		count;
	char	**fd;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (argv[i++][0] == '>')
			if (argv[i - 1][1] == '\0')
				if (argv[i] != NULL)
					count++;
	}
	i = 0;
	fd = malloc(sizeof(char *) * (count + 1));
	while (*argv != NULL)
	{
		if ((*(argv++))[0] == '>')
			if ((*(argv - 1))[1] == '\0')
				if (*(argv) != NULL)
					fd[i++] = ft_strdup(*(argv));
	}
	fd[i] = NULL;
	return (fd);
}

char	**del_fdi(char **argv, int i, int i2)
{
	while (argv[i])
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
		{
			free(argv[i]);
			free(argv[i + 1]);
			while (argv[i + i2] != NULL)
			{
				if (argv[i + i2 + 1] == NULL)
				{	
					argv[i + i2] = argv[i + i2 + 1];
					break ;
				}
				argv[i + i2] = argv[i + i2 + 2];
				i2++;
			}
			i2 = 0;
		}
		if (argv[i] == NULL)
			break ;
		if (argv[i][0] != '<' && argv[i][0] != '>')
		i++;
	}
	return (argv);
}
