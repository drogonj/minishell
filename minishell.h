/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:58:49 by fcherrie          #+#    #+#             */
/*   Updated: 2023/03/06 15:23:06 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0
# define HISTORY ".history"

typedef int	t_bool;

typedef struct s_cmd
{
	char			**line;
	char			**fdi1;
	char			**fdi2;
	char			**fdo1;
	char			**fdo2;
	char			*ilast;
	char			*olast;
	int				fdi;
	int				fdo;
	int				pid;
	int				opt;
	void			(*function)(struct s_cmd *);
	int				redirection;
	struct s_core	*core;
}					t_cmd;

typedef struct s_core
{
	t_bool	is_running;
	t_cmd	**cmd_village;
	char	**cmd;
	char	*line;
	char	**env;
	int		heredoc;
	int		error;
	int		pid;
	int		history_fd;
}			t_core;

int			pars_line(t_core *core, char *line);
char		*check_variable_line(t_core *core);
int			launch_multi_cmd(t_core *core, t_cmd **cmd);
int			check_end_pipe(char **cmd);
char		*cat_pipe(t_core *core, char *line);
char		**splitline(const char *s, char c);
int			check_quote(char *line);
int			count_pipe(t_cmd **cmd);
char		**ft_free_tab(char **tab);
char		*search_var(char *line);
char		*replace_variable(t_core *core, char *var, char *line);
void		check_variable(t_core *core, char **cmd);
int			modify_line(t_core *core, char **cmd);
char		**ft_free_tab(char **tab);
char		*cat_variable(char *line, char *var, int size);
void		check_error_var(t_core *core, char **cmd);

void		trans_dol(char *line);
void		trans_sub(char *line);
char		*trans_quote(char *line, int i, char *start);

// --- Signals --- //
void		handle_ctrl_c(int sig);
void		handle_ctrl_c_heredoc(int sig);
void		handle_ctrl_backslash(int sig);
void		handle_ctrl_d(int sig);
int			matrix(int commit, int error_val);
int			johnny(t_bool change_static, int command_status);

// --- Redirection --- //
int			set_fork(t_cmd *next, t_cmd *cmd, int fdi, int fdo);
char		*loc_last(char **line, char fd);
char		**del_fdi(char **argv, int i, int i2);
char		**locate_fdo1(char **argv);
char		**locate_fdo2(char **argv);
char		**locate_fdi1(char **argv);
char		**locate_fdi2(char **argv);
void		set_pipe_cmd(t_cmd **cmd, int i);
int			open_fdo(char **fdo1, char **fdo2, t_cmd *cmd, int i);
int			open_fdi(char **fdi1, char **fdi2, t_cmd *cmd, int i);
void		close_fd(int i, int i2);
int			error_fd(t_cmd *cmd, char *fdi, int error);

// --- T_cmd gestion --- //
void		launch_cmd(t_core *core, t_cmd **cmd);
void		is_builtin(char *s, t_cmd *cmd);
void		init_t_cmd(t_core *core, char **line);
t_cmd		*init_cmd(t_core *core, t_cmd *head);
int			cmd_lstsize(t_cmd *head);
t_cmd		*cmd_last(t_cmd *head);
void		cmd_add_back(t_cmd **head, t_cmd *new);
int			ext_command(t_core *core, t_cmd *cmd);
void		cmd_lstclear(t_cmd **head);

// --- Builtins --- //
void		builtin_echo(t_cmd *cmd);
void		builtin_env(t_cmd *cmd);
void		builtin_pwd(t_cmd *cmd);
void		builtin_export(t_cmd *cmd);
char		**copy_env_sorted(char **env);
void		put_export_var(char *s, int fdo);
void		builtin_unset(t_cmd *cmd);
void		builtin_exit(t_cmd *cmd);
int			free_core(t_core *core, int function, t_bool must_exit);
void		builtin_cd(t_cmd *cmd);
char		*find_path_executable(char **env, char *command);
void		launch_executable(t_cmd *cmd);
void		builtin_export_export(t_cmd *cmd, char **var);
void		loop_heredoc(char *end, int p, int w);

//	---	Utils --- //
int			contain_char(char *s, char c);
void		*ft_realloc_tab(char **ptr, size_t new_size);
int			tab_len(char **tab);
char		*ft_strjoin_msh(char *s1, char *s2);
void		*ft_memcpy_msh(char **dst, char **src, size_t n);
int			contain_var(char **env, char *var, int n);
char		*remove_char(char **s, char c);
int			contain_invalid(char *s, char *excludes);
int			export_contain_plus(t_cmd *cmd, int *plus, int i);
char		**ft_split_export(char *s);
long int	ft_strlen_varname(char *str);
char		*ft_getenv(char **env, char *var);
void		print_core(t_core *core);
void		add_mnsh_history(t_core *core, char **line);
int			contain_redirection(char **tab);
void		re_init_core(t_core *core);
int			set_error(t_core *core, int error, int function);
void		load_shlvl(char **shlvl);
void		*ft_free(void *p);
void		remake_underscore_env_var(t_cmd *cmd, t_bool to_null);
int			ret_error_and_free(char **s, char **s2, char **t, char **t2);
void		create_env_var(t_core *core, char *var);
int			count_char(char *s, char to_find);
int			fatal_error(t_core *core);

#endif
