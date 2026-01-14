/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:51:10 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/21 08:51:10 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expansion_loop(t_gen_data *data, char **env, char **new_str)
{
	char	*env_var;
	char	*tmp;
	int		i;

	env_var = NULL;
	i = 0;
	while ((*new_str)[i])
	{
		if ((*new_str)[i] == '$' && (*new_str)[i + 1])
		{
			if (env_var)
				free(env_var);
			env_var = env_var_str(*new_str, i + 1, data, env);
			tmp = *new_str;
			*new_str = ft_strinsert(*new_str, env_var, i, data->env_size + 1);
			if (!*new_str)
				fatal_error(data, "malloc");
			free(tmp);
			i += ft_strlen(env_var);
		}
		else
			i++;
	}
	free(env_var);
}

char	*expansion_setup(t_gen_data *data, char *token_text, char **env)
{
	char	*new_str;

	new_str = ft_strdup(token_text);
	if (!new_str)
		fatal_error(data, "malloc");
	expansion_loop(data, env, &new_str);
	return (new_str);
}

void	heredoc_handler(t_gen_data *data, char **env)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		generate_heredocs(data, env);
		free_tmp_filenames(data);
		close_fds(data);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &g_signal_status, 0);
		if (WIFSIGNALED(g_signal_status))
		{
			data->last_exit_status = 128 + WTERMSIG(g_signal_status);
			write(1, "\n", 1);
		}
		else
			data->last_exit_status = WEXITSTATUS(g_signal_status);
		if (data->last_exit_status == 1)
			data->exit_loop = 1;
	}
}

void	expand_token(t_gen_data *data, char **env)
{
	char	*tmp;
	int		i;

	if (data->exit_loop != 0)
		return ;
	i = 0;
	heredoc_handler(data, env);
	signal(SIGINT, signal_handler);
	while (data->executables[i])
	{
		if (data->executables[i]->expand == 1
			&& data->executables[i]->type == WORD
			&& data->executables[i]->quote != SINGLE)
		{
			tmp = data->executables[i]->text;
			data->executables[i]->text = expansion_setup(
					data, data->executables[i]->text, env);
			free(tmp);
		}
		i++;
	}
}
