/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:54:07 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:48:19 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loc_last(char **line, char fd)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (i != -1)
	{
		if (line[i][0] == fd)
			return (ft_strdup(line[++i]));
		i--;
	}
	return (NULL);
}

int	open_fdo(char **fdo1, char **fdo2, t_cmd *cmd, int i)
{
	int	fd;

	while (fdo1[i])
	{
		if (fdo1[i][0] == '\0')
			return (error_fd(cmd, fdo1[i], 2));
		fd = open(fdo1[i++], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (ft_strncmp(fdo1[i - 1], cmd->olast, ft_strlen(fdo1[i - 1])) == 0)
			cmd->fdo = fd;
		else
			close(fd);
	}
	i = 0;
	while (fdo2[i])
	{
		if (fdo2[i][0] == '\0')
			return (error_fd(cmd, fdo2[i], 2));
		fd = open(fdo2[i++], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (ft_strncmp(fdo2[i - 1], cmd->olast, ft_strlen(fdo2[i - 1])) == 0)
			cmd->fdo = fd;
		else
			close(fd);
	}
	return (0);
}

void	write_fdi2(char *end, int w, t_cmd *cmd)
{
	int		p[2];
	int		pid;

	if (w == 1)
	{
		pipe(p);
		cmd->fdi = p[0];
	}
	signal(SIGINT, handle_ctrl_c_heredoc);
	pid = fork();
	if (pid == 0)
	{
		if (w == 1)
		{
			close(p[0]);
			loop_heredoc(end, p[1], w);
		}
		else
			loop_heredoc(end, 0, 0);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (w == 1)
		close(p[1]);
	signal(SIGINT, handle_ctrl_c);
}

int	error_fd(t_cmd *cmd, char *fdi, int error)
{
	if (error == 1)
	{
		if (cmd->line[0])
			cmd->line[0][0] = '\0';
		cmd->function = NULL;
		printf("minishell: no such file or directory: %s\n", fdi);
		return (1);
	}
	if (error == 2)
	{
		if (cmd->line[0])
			cmd->line[0][0] = '\0';
		cmd->function = NULL;
		printf("minishell: ambigous redirect:%s\n", fdi);
		return (1);
	}
	return (0);
}

int	open_fdi(char **fdi1, char **fdi2, t_cmd *cmd, int i)
{
	int	fd;

	i = 0;
	while (fdi1[i])
	{
		if (fdi1[i][0] == '\0')
			return (error_fd(cmd, fdi1[i], 2));
		fd = open(fdi1[i++], O_RDONLY);
		if (fd < 0)
			return (error_fd(cmd, fdi1[i -1], 1));
		if (ft_strncmp(fdi1[i - 1], cmd->ilast, ft_strlen(fdi1[i - 1])) == 0)
			cmd->fdi = fd;
		else
			close(fd);
	}
	i = -1;
	while (fdi2[++i])
	{
		if (ft_strncmp(fdi2[i], cmd->ilast,
				ft_strlen(fdi2[i]) + ft_strlen(cmd->ilast)) == 0)
			write_fdi2(fdi2[i], 1, cmd);
		else
			write_fdi2(fdi2[i], 0, cmd);
	}
	return (0);
}
