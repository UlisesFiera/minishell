/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:03:57 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 10:03:02 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/* Data structs */

typedef struct s_gen_data
{
	char	*username;
	char	*final_prompt;
	char	*input;
	char	**executables;
} 	t_gen_data;

/* Shell functionalities */

char	*read_input(t_gen_data *data);
void	parse_input(t_gen_data *data);
void	*init_data(t_gen_data *data);
void	free_data(t_gen_data *data);
void	free_exec(t_gen_data *data);
void	exec_command(t_gen_data *data, char **env);
int		exec_counter(char *input);
char	*exec_split(char *input, int *index);
int		exec_counter(char *input);
int		find_closing_quote(char *input, int index);

#endif