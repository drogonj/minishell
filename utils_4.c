/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:53:36 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/15 13:53:39 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_error_and_free(char **str, char **str2, char **tab, char **tab2)
{
	if (str && *str)
		free(*str);
	if (str2 && *str2)
		free(*str2);
	if (tab)
		ft_free_tab(tab);
	if (tab2)
		ft_free_tab(tab2);
	return (1);
}

void	create_env_var(t_core *core, char *var)
{
	int	tablen;

	if (!var || var[0] == 0)
		return ;
	tablen = tab_len(core->env);
	core->env = ft_realloc_tab(core->env,
			(tablen + 2) * sizeof(char *));
	if (!core->env)
		free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	core->env[tablen] = ft_strdup(var);
	if (!core->env[tablen])
		free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
}

int	count_char(char *s, char to_find)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	if (!s)
		return (0);
	while (s[++i])
		if (s[i] == to_find)
			res++;
	return (res);
}

int	fatal_error(t_core *core)
{
	free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	return (-1);
}

void	*ft_free(void *p)
{
	free(p);
	return (NULL);
}
