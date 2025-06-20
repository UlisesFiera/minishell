/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:03:57 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 19:58:38 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREEN "\001\033[38;5;22m\002"
# define RESET  "\001\033[0m\002"

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <dirent.h>

/* Data structs */

extern int	g_in_secondary_prompt;

typedef struct s_gen_data
{
	char	*username;
	char	*final_prompt;
	char	*input;
	char	**executables;
	int		*quotes;
	int		*cat_quotes;
	int		pipe_flag;
	int		input_fd;
	int		output_fd;
	int		pipe_index;
	int		*tmp_fds;
	char	**tmp_filenames;
	int		exit_status;
	int		last_exit_status;
	int		executable_pos;
	int		lineno;
	int		exec_count;
	char	**clean_array;
	int		*updated_quotes;
	char	**exec_copy;
	int		env_var_index;
	int		pipe_end;
}	t_gen_data;

/* Shell functionalities */

char	*read_input(t_gen_data *data, char *prompt, int check_on);
void	parse_input(t_gen_data *data, char **env);
void	init_data(t_gen_data *data);
void	free_data(t_gen_data *data);
void	free_exec(t_gen_data *data);
void	exec_command(t_gen_data *data, char **env);
int		exec_counter(char *input);
char	*exec_split(int *index,
			int command_index, t_gen_data *data);
int		exec_counter(char *input);
int		find_quote(char *input, int index);
char	*ft_get_path(char *cmd, char **env);
void	ft_free_tab(char **tab);
char	*ft_getenv(char *env_name, char **env);
int		ft_strcmp(char *s1, char *s2);
char	**array_cleaner_left(t_gen_data *data);
char	**array_cleaner_right(t_gen_data *data, int optcode, char *symbol);
char	**array_cleaner(t_gen_data *data, char *symbol);
void	reset_prompt(void);
void	exec_pipe(t_gen_data *data, char **env);
int		file_finder(char **command_array);
void	init_quotes(t_gen_data *data, int exec_count);
char	**pipe_divider(char **commands, int index);
char	*ft_strinsert(char *string, char *insert, int index, int skip);
void	signal_handler(int signal);
int		is_only_spaces(char *str);
char	*expand_env(char *executable, char **env, t_gen_data *data);
char	*get_env_var(char *executable, char **env, t_gen_data *data);
void	parse_env_vars_quotes(t_gen_data *data,
			char **env, char *command, int index);
void	replace_env(t_gen_data *data, char **env_paths, char **env);
void	syntax_error(char *token, t_gen_data *data);
int		ft_is_only_spaces(char *str);
int		syntax_check(char *line, t_gen_data *data);
int		find_quote(char *input, int index);
int		reverse_find_quote(char *input, int index);
int		odd_quotes(char *input, int index);
void	welcome_message(t_gen_data *data);
void	signal_handler(int signal);
void	reset_prompt(void);
void	signal_handler_redir(int signal);
void	free_tmp_filenames(t_gen_data *data);
void	env_var_check(t_gen_data *data, char **env);
void	reset_data(t_gen_data *data);

/* Parsing */

char	*parse_env_vars(t_gen_data *data, char *line, char **env);

/* Execution */

void	exec_env(t_gen_data *data, char **env);
void	exec_built(t_gen_data *data, char *command);
void	execve_handler(char *cmd_path, t_gen_data *data, char **env);

/* Redirections */

int		redirect(t_gen_data *data, char **env);
void	exec_from_input(t_gen_data *data, int index, char *cmd_path);
void	exec_to_output(t_gen_data *data, int index, char *cmd_path);
void	exec_append(t_gen_data *data, int index, char *cmd_path);
void	exec_heredoc(t_gen_data *data);
void	generate_heredocs(t_gen_data *data, char **env);
void	collect_input(t_gen_data *data, int index, int count, char **env);
void	remove_temps(void);
int		find_executable(t_gen_data *data);
char	**executables_copy(t_gen_data *data);
int		pipe_index(t_gen_data *data, char **commands);
void	set_pipe_flag(t_gen_data *data);
void	pipe_executable(int *index, char *executable);
void	child_redirect_handler(t_gen_data *data, char **clean_commands,
			char **env, char *cmd_path);

/* Built-ins */

void	echo(char **commands);

/* Errors */

void	heredoc_error(t_gen_data *data, char *delimiter, int count);

#endif