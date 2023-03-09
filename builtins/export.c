/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:42 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/30 11:49:56 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export_export(t_cmd *cmd, char **var)
{
	int	tablen;

	if (!var || var[0] == 0)
		return ;
	tablen = tab_len(cmd->core->env);
	cmd->core->env = ft_realloc_tab(cmd->core->env,
			(tablen + 2) * sizeof(char *));
	if (!cmd->core->env)
		fatal_error(cmd->core);
	cmd->core->env[tablen] = ft_strdup(var[0]);
	if (!cmd->core->env[tablen])
		fatal_error(cmd->core);
	if (var[1])
	{
		cmd->core->env[tablen] = ft_strjoin_msh(cmd->core->env[tablen], "=");
		cmd->core->env[tablen] = ft_strjoin_msh(cmd->core->env[tablen], var[1]);
		if (!cmd->core->env[tablen])
			fatal_error(cmd->core);
	}
}

void	modify_var(t_cmd *cmd, char **var, int indice)
{
	char			*new_val;

	var[0] = remove_char(&var[0], '+');
	new_val = ft_strdup(var[0]);
	if (!new_val)
		fatal_error(cmd->core);
	if (var[1])
	{
		new_val = ft_strjoin_msh(new_val, "=");
		new_val = ft_strjoin_msh(new_val, var[1]);
		if (!new_val)
			fatal_error(cmd->core);
	}
	if (!new_val)
		return ;
	free(cmd->core->env[indice]);
	cmd->core->env[indice] = new_val;
}

static void	builtin_export_ter(t_cmd *cmd, int contain, char **val, int plus)
{
	if (plus == 1 && contain != -1 && tab_len(val) > 1)
	{
		if (contain_char(cmd->core->env[contain], '=') == -1)
		{
			cmd->core->env[contain] = ft_strjoin_msh
				(cmd->core->env[contain], "=");
			if (!cmd->core->env[contain])
				fatal_error(cmd->core);
		}
		cmd->core->env[contain] = ft_strjoin_msh
			(cmd->core->env[contain], val[1]);
		if (!cmd->core->env[contain])
			fatal_error(cmd->core);
	}
	else if (contain != -1 && tab_len(val) > 1)
		modify_var(cmd, val, contain);
	else if (contain == -1)
		builtin_export_export(cmd, val);
}

static void	builtin_export_bis(t_cmd *cmd, int i, char **val, int contain_val)
{
	int		plus;

	if (cmd->line[1][0] == '=')
		set_error(cmd->core, 42,
			ft_printf(2, "minishell: export: '=': not a valid identifier\n"));
	else
	{
		while (cmd->line[++i])
		{
			val = ft_split_export(cmd->line[i]);
			if (!val || !val[0])
				return ;
			if (export_contain_plus(cmd, &plus, i) == 1)
				val[0] = remove_char(&val[0], '+');
			contain_val = contain_var(cmd->core->env, val[0],
					ft_strlen(val[0]));
			if (contain_invalid(val[0], 0) != -1)
				set_error(cmd->core, 42, ft_printf(2,
						"minishell: export: '%c': not a valid identifier\n",
						val[0][contain_invalid(val[0], 0)]));
			else
				builtin_export_ter(cmd, contain_val, val, plus);
			ft_free_tab(val);
		}
	}
}

void	builtin_export(t_cmd *cmd)
{
	char	**tmp_env;
	char	**val;
	int		contain_var_val;
	int		i;

	i = -1;
	val = 0;
	contain_var_val = -1;
	cmd->core->error = 0;
	if (!cmd->line || !cmd->line[0] || !cmd->line[0][0])
		cmd->core->error = 1;
	else if (tab_len(cmd->line) == 1)
	{
		tmp_env = copy_env_sorted(cmd->core->env);
		while (tmp_env[++i])
		{
			if (i == contain_var(tmp_env, "_", 1))
				continue ;
			ft_putstr_fd("declare -x ", cmd->fdo);
			put_export_var(tmp_env[i], cmd->fdo);
		}
		ft_free_tab(tmp_env);
	}
	else
		builtin_export_bis(cmd, 0, val, contain_var_val);
}
