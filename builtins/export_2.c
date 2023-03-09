/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:23:23 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/31 16:23:24 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env_sorted(char **env)
{
	int		i;
	int		j;
	char	**env_copy;
	char	*save;

	env_copy = (char **)ft_calloc(tab_len(env) + 1, sizeof(char *));
	if (!env_copy)
		return (0);
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(env[i]);
	i = 0;
	while (++i < tab_len(env_copy))
	{
		save = env_copy[i];
		j = i - 1;
		while (j >= 0 && ft_strncmp(env_copy[j], save,
				ft_strlen(env_copy[j])) > 0)
		{
			env_copy[j + 1] = env_copy[j];
			j -= 1;
		}
		env_copy[j + 1] = save;
	}
	return (env_copy);
}

void	put_export_var(char *s, int fdo)
{
	int		i;
	t_bool	need_quotes;

	if (!s)
		return ;
	i = -1;
	need_quotes = FALSE;
	while (s[++i])
	{
		ft_putchar_fd(s[i], fdo);
		if (s[i] == '=' && need_quotes == FALSE)
		{
			ft_putchar_fd('\"', fdo);
			need_quotes = TRUE;
		}
	}
	if (need_quotes == TRUE)
		ft_putchar_fd('\"', fdo);
	ft_putchar_fd('\n', fdo);
}
