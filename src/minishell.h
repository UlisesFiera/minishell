/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:03:57 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/30 21:29:50 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define GREEN "\001\033[38;5;22m\002"
# define RESET "\001\033[0m\002"
# define INULL -918273645

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <sys/resource.h>

extern int	g_signal_status;

/* Data structs */

typedef enum s_token_type
{
	WORD,
	REDIRECTOR,
	DELIMITER,
	TARGET,
	COMMAND,
	ARG,
	PIPE
}	t_token_type;

typedef enum s_quote_type
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote_type;

typedef enum s_redirector_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirector_type;

typedef struct s_token
{
	char			*text;
	t_token_type	type;
	t_quote_type	quote;
	int				expand;
	int				merge;
}					t_token;

typedef struct s_redirector
{
	t_redirector_type	type;
	char				*target_file;
}						t_redirector;

typedef struct s_command
{
	char				**argv;
	t_quote_type		quote;
	t_redirector		**redirections;
}						t_command;

typedef struct s_gen_data
{
	char		*input;
	char		*username;
	char		*final_prompt;
	int			token_index;
	t_token		**executables;
	int			pipe_flag;
	int			pipe_count;
	int			*pipe_ends;
	int			*tmp_fds;
	char		**tmp_filenames;
	int			exit_loop;
	int			last_exit_status;
	int			prev_exit_status;
	int			executable_pos;
	int			lineno;
	int			exec_count;
	char		**exec_env;
	char		**exec_env_export;
	int			env_size;
	int			heredoc_count;
	t_command	**command_array;
	int			exp_token_size;
	int			redir_count;
}			t_gen_data;

/* Main functionalities */

void		init_data(t_gen_data *data, char **env);
void		load_username(t_gen_data *data);
void		load_env(t_gen_data *data, char **env);
void		load_export(t_gen_data *data, char **env);
void		signal_handler(int signal);
void		welcome_message(void);
void		read_input(t_gen_data *data, char *prompt, int check_on);
void		free_data(t_gen_data *data);
void		reset_prompt(void);
void		free_tmp_filenames(t_gen_data *data);
void		reset_data(t_gen_data *data);
void		free_commands(t_command ***commands);
void		free_tokens(t_gen_data *data);

/* Expansion */

void		expand_token(t_gen_data *data, char **env);
char		*expansion_setup(t_gen_data *data, char *token_text, char **env);
char		*env_var_str(char *line, int i, t_gen_data *data, char **env);
void		field_split(t_gen_data *data);
int			field_size(char *var_text, int *index, int *i_first);
void		alloc_token(
				t_gen_data *data, t_token **exp_array, int i_new, int i_old);
void		merge_quotes(t_gen_data *data, t_token **exp_array);

/* Parsing */

void		parse_input(t_gen_data *data);
void		exec_counter(t_gen_data *data);
t_token		*exec_split(t_gen_data *data);
int			skip_space_tab_nl(t_gen_data *data, int index);
int			skip_space_tab_nl_field(char *var_text, int index);

/* Execution */

void		execution_setup(t_gen_data *data, char **env);
void		pipeline_stream(t_command **commands, t_gen_data *data, char **env);
int			execute_command(t_command *command, t_gen_data *data, char **env);
t_command	*command_fill(t_gen_data *data, int index);
void		execution_stream(
				t_command **commands, t_gen_data *data, char **env);
int			execve_handler(t_command *command, char **env);
int			execute_env_command(
				t_command *command, t_gen_data *data, char **env);
int			builtin_handler(char *builtin, t_command *command,
				t_gen_data *data, char **env);
int			execute_builtin(char *builtin, t_command *command,
				t_gen_data *data, char **env);
char		*builtin_finder(char *executable);
t_command	**command_array_builder(
				t_command **command_array, t_gen_data *data, int size);

/* Redirections */

int			redirect_setup(t_command *command, t_gen_data *data);
void		close_fds(t_gen_data *data);
void		free_heredoc(t_gen_data *data);
void		generate_heredocs(t_gen_data *data, char **env);
void		collect_input(t_gen_data *data, int index, int count, char **env);
void		remove_temps(void);
void		heredoc_count(t_gen_data *data);
char		*expand_heredoc(
				t_gen_data *data, int index, char **env, char **line);
char		*file_name_generator(int findex, t_gen_data *data);
int			heredoc(t_redirector *redirector, t_gen_data *data);
int			append(t_redirector *redirector);
int			to_output(t_redirector *redirector);
int			from_input(t_redirector *redirector);
void		redir_assign(t_command *command, t_gen_data *data, int index);

/* Built-ins */

int			echo(t_gen_data *data, t_command *command);
int			cd(char **commands);
int			pwd(t_gen_data *data);
int			env(char **exec_env);
void		exec_env(t_gen_data *data, char **env);
void		free_env(char **exec_env);
int			export(t_gen_data *data, char **executables, char **exec_env);
void		export_empty_args(t_gen_data *data, char **exec_env);
void		export_var_exp1(t_gen_data *data, char *var);
void		export_var_env(t_gen_data *data, char *var);
void		export_var_exp2(t_gen_data *data, char *var);
void		export_exit_status(t_gen_data *data, int valid, int invalid);
void		sort_export(char **env);
void		drop_duplicated(t_gen_data *data);
char		**update_env(char **old_env, int size, int flag);
int			are_duplicated(t_gen_data *data, int i, int j);
int			find_env_var(char **environ, char *var_name);
int			find_env_var_2(char **environ, char *var_name);
char		**add_env_var(char **env, char *new_var);
int			check_valid_var_name(char *var);
void		print_export(char *env_var);
int			has_equal(char *var);
int			unset(t_gen_data *data, char **commands);
int			exit_minishell(t_gen_data *data, char **commands);
void		exit_handler(t_gen_data *data, int exit_status);

/* Errors */

void		heredoc_error(t_gen_data *data, char *delimiter);
void		unclosed_token_error(char *token, t_gen_data *data);
void		fatal_error(t_gen_data *data, char *error_code);
void		syntax_error(char *token, t_gen_data *data, int optcode);
int			exec_error(t_command *command, char **cmd_path, int errcode);

/* Utils */

int			find_closing_quote(t_gen_data *data, int index);
char		*ft_get_path(char *cmd, char **env);
void		ft_free_tab(char ***tab);
char		*ft_getenv(char *env_name, char **env);
int			ft_strcmp(char *s1, char *s2);
int			file_finder(char **command_array);
char		*ft_strinsert(char *string, char *insert, int index, int skip);
char		*get_env_var(char *executable, char **env, t_gen_data *data);
int			ft_is_only_spaces(char *str);
int			odd_quotes(char *input, int index);
int			ft_is_digit_args(char *args);

#endif