/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:58:47 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/15 13:52:24 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_history(t_core *core)
{
	char	*buffer;

	buffer = 0;
	core->history_fd = open(HISTORY, O_CREAT | O_RDWR, S_IRWXU);
	if (core->history_fd == -1)
		free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	buffer = get_next_line(core->history_fd);
	while (buffer != 0)
	{
		add_history(buffer);
		free(buffer);
		buffer = 0;
		buffer = get_next_line(core->history_fd);
	}
}

static char	**init_env(char **env)
{
	char	**minishell_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	minishell_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!minishell_env)
		return (0);
	i = -1;
	while (env[++i])
	{
		minishell_env[i] = ft_strdup(env[i]);
		if (ft_strncmp(minishell_env[i], "SHLVL", 5) == 0)
			load_shlvl(&minishell_env[i]);
		if (!minishell_env[i])
		{
			ft_free_tab(minishell_env);
			return (0);
		}
	}
	return (minishell_env);
}

static t_core	*init_core(char **env)
{
	t_core	*core;

	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
	{
		ft_printf(2, "minishell: fatal error\n");
		exit(EXIT_FAILURE);
	}
	core->is_running = TRUE;
	core->cmd = NULL;
	core->error = 0;
	core->env = init_env(env);
	core->cmd_village = 0;
	core->line = NULL;
	core->history_fd = 0;
	if (!core->env)
		free_core(core, ft_printf(2, "minishell: fatal error\n"), TRUE);
	return (core);
}

int	main(int argc, char **argv, char **env)
{
	t_core	*core;

	(void)argc;
	(void)argv;
	core = init_core(env);
	init_history(core);
	rl_catch_signals = 0;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
	while (core->is_running)
	{
		core->line = readline("minishell> ");
		add_mnsh_history(core, &(core->line));
		if (pars_line(core, core->line) == 0)
		{
			init_t_cmd(core, core->cmd);
			launch_cmd(core, core->cmd_village);
			re_init_core(core);
		}
		else
			free(core->line);
	}
	free_core(core, 0, FALSE);
	return (0);
}
