/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:20:54 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/15 13:53:12 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	matrix(int set_error, int error_val)
{
	static t_bool	need_error = FALSE;

	if (need_error == TRUE)
	{
		need_error = FALSE;
		return (1);
	}
	if (set_error == 1)
		need_error = TRUE;
	return (error_val);
}

int	johnny(t_bool modify_status, t_bool new_status)
{
	static t_bool	command_on = FALSE;

	if (modify_status == TRUE)
		command_on = new_status;
	return (command_on);
}

void	handle_ctrl_c(int sig)
{
	(void)sig;
	rl_redisplay();
	ft_printf(1, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (johnny(FALSE, FALSE) == FALSE)
		rl_redisplay();
	matrix(1, 0);
}

void	handle_ctrl_c_heredoc(int sig)
{
	(void)sig;
	ft_printf(1, "\n");
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
}
