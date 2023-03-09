/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:44:01 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/15 13:44:04 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long int	ft_atoi_long_long(const char *str)
{
	size_t					i;
	int						sign;
	unsigned long long int	res;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + str[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	ft_isdigit_shlvl(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_first(char **shlvl)
{
	char	**splitted;

	splitted = ft_split_export(*shlvl);
	if (!splitted)
		return (-1);
	if (ft_isdigit_shlvl(splitted[1]) == 1)
	{
		free(*shlvl);
		ft_free_tab(splitted);
		*shlvl = ft_strdup("SHLVL=1");
		return (-1);
	}
	ft_free_tab(splitted);
	return (0);
}

void	load_shlvl(char **shlvl)
{
	char			**splitted;
	long long int	converted;
	char			*itoa_var;

	splitted = ft_split_export(*shlvl);
	if (!splitted || check_first(shlvl) == -1)
		return ;
	free(*shlvl);
	converted = ft_atoi_long_long(splitted[1]);
	ft_free_tab(splitted);
	if (converted > 1999999)
	{
		ft_printf(2, "minishell: warning: shell level "
			"(%u) too high, resetting to 1\n", (unsigned int)converted);
		*shlvl = ft_strdup("SHLVL=1");
	}
	else if (converted < 0)
		*shlvl = ft_strdup("SHLVL=0");
	else
	{
		itoa_var = ft_itoa(converted + 1);
		*shlvl = ft_strdup("SHLVL=");
		*shlvl = ft_strjoin_msh(*shlvl, itoa_var);
		free(itoa_var);
	}
}

void	remake_underscore_env_var(t_cmd *cmd, t_bool to_null)
{
	const int	len = tab_len(cmd->line);
	const int	i = contain_var(cmd->core->env, "_=", 2);

	if (!len || i == -1)
		return ;
	free(cmd->core->env[i]);
	cmd->core->env[i] = ft_strdup("_=");
	if (!cmd->core->env[i])
		return ;
	if (to_null == FALSE)
		cmd->core->env[i] = ft_strjoin_msh
			(cmd->core->env[i], cmd->line[len - 1]);
}
