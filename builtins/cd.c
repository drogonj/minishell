/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:26 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/30 11:49:52 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_param(char *s, t_cmd *cmd)
{
	if (!s)
		return (1);
	if (s[0] == '~' && ft_strlen(s) == 1)
	{
		if (count_char(s, '~') > 1)
		{
			cmd->core->error = 1;
			return (-2);
		}
		else
			return (1);
	}
	if (s[0] == '-')
	{
		if (ft_strlen(s) == 1)
			return (2);
		ft_printf(2, "minishell: cd: invalid option\ncd: usage: cd [dir]\n");
		cmd->core->error = 1;
		return (-1);
	}
	return (0);
}

static int	go_to_home_dir(t_cmd *cmd, char *home_dir, char *old_pwd_dir)
{
	if (!home_dir || chdir(home_dir) != 0)
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return (ret_error_and_free(&home_dir, &old_pwd_dir, 0, 0));
	}
	if (tab_len(cmd->line) > 1)
	{
		cmd->line[1][0] = '.';
		if (chdir(cmd->line[1]) != 0)
			return (ret_error_and_free(&home_dir, &old_pwd_dir, 0, 0));
	}
	free(home_dir);
	free(old_pwd_dir);
	return (0);
}

static int	treat_param(t_cmd *cmd, int param)
{
	char	*home_dir;
	char	*old_pwd_dir;

	home_dir = ft_getenv(cmd->core->env, "HOME");
	old_pwd_dir = ft_getenv(cmd->core->env, "OLDPWD");
	if (param == 1)
		return (go_to_home_dir(cmd, home_dir, old_pwd_dir));
	else if (param == 2)
	{
		if (!old_pwd_dir || chdir(old_pwd_dir) != 0)
		{
			ft_printf(2, "minishell: cd: OLDPWD not set\n");
			return (ret_error_and_free(&home_dir, &old_pwd_dir, 0, 0));
		}
		builtin_pwd(cmd);
	}
	free(home_dir);
	free(old_pwd_dir);
	return (0);
}

static void	refresh_env(t_cmd *cmd, char *pathsave, char *newpath, int i)
{
	if (contain_var(cmd->core->env, "OLDPWD", 6) == -1)
		create_env_var(cmd->core, "OLDPWD");
	while (cmd->core->env[++i])
	{
		if (ft_strncmp(cmd->core->env[i], "PWD",
				ft_strlen_varname(cmd->core->env[i])) == 0)
		{
			free(cmd->core->env[i]);
			cmd->core->env[i] = ft_strdup("PWD=");
			cmd->core->env[i] = ft_strjoin_msh(cmd->core->env[i], newpath);
			if (!cmd->core->env[i])
				fatal_error(cmd->core);
		}
		if (strncmp(cmd->core->env[i], "OLDPWD",
				ft_strlen_varname(cmd->core->env[i])) == 0)
		{
			free(cmd->core->env[i]);
			cmd->core->env[i] = ft_strdup("OLDPWD=");
			cmd->core->env[i] = ft_strjoin_msh(cmd->core->env[i], pathsave);
			if (!cmd->core->env[i])
				fatal_error(cmd->core);
		}
	}
}

void	builtin_cd(t_cmd *cmd)
{
	const int	param = is_param(cmd->line[1], cmd);
	char		*pathsave;
	char		*newpath;

	pathsave = 0;
	pathsave = getcwd(pathsave, 0);
	newpath = 0;
	if (tab_len(cmd->line) == 1 || param > 0)
		cmd->core->error = treat_param(cmd, param);
	else if (param != -1)
	{
		if (chdir(cmd->line[1]) != 0)
		{
			ft_printf(2, "minishell: cd: %s: ", cmd->line[1]);
			perror("");
			cmd->core->error = 1;
		}
		else
			cmd->core->error = 0;
	}
	if (cmd->core->error == 0)
		refresh_env(cmd, pathsave, newpath = getcwd(newpath, 0), -1);
	free(pathsave);
	if (newpath)
		free(newpath);
}
