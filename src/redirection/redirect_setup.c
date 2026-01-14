/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:42:19 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 17:10:03 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_handler(t_command *command, t_gen_data *data, int i)
{
	int	status;

	status = 0;
	if (command->redirections[i]->type == INPUT)
		status = from_input(command->redirections[i]);
	else if (command->redirections[i]->type == OUTPUT)
		status = to_output(command->redirections[i]);
	else if (command->redirections[i]->type == APPEND)
		status = append(command->redirections[i]);
	else if (command->redirections[i]->type == HEREDOC)
		status = heredoc(command->redirections[i], data);
	return (status);
}

int	redirect_setup(t_command *command, t_gen_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (command->redirections[i])
	{
		status = redir_handler(command, data, i);
		if (status != 0)
			return (status);
		i++;
	}
	return (status);
}

void	assign_redir_type(
			t_gen_data *data, t_redirector **redirections, int i_start, int i)
{
	if (!redirections[i])
		fatal_error(data, "malloc");
	if (!ft_strcmp(data->executables[i_start]->text, "<"))
		redirections[i]->type = INPUT;
	else if (!ft_strcmp(data->executables[i_start]->text, "<<"))
		redirections[i]->type = HEREDOC;
	else if (!ft_strcmp(data->executables[i_start]->text, ">"))
		redirections[i]->type = OUTPUT;
	else if (!ft_strcmp(data->executables[i_start]->text, ">>"))
		redirections[i]->type = APPEND;
}

void	redir_fill(t_gen_data *data, t_redirector **redirections, int i_start)
{
	int		i;
	char	*target;

	i = 0;
	while (data->executables[i_start]
		&& data->executables[i_start]->type != PIPE)
	{
		if (data->executables[i_start]->type == REDIRECTOR)
		{
			target = data->executables[i_start + 1]->text;
			redirections[i] = malloc(sizeof(t_redirector));
			assign_redir_type(data, redirections, i_start, i);
			redirections[i]->target_file = ft_strdup(target);
			if (!redirections[i]->target_file)
				fatal_error(data, "malloc");
			i++;
		}
		i_start++;
	}
}

void	redir_assign(t_command *command, t_gen_data *data, int index)
{
	t_redirector	**redirections;
	int				size;
	int				i_start;

	size = 0;
	while (index > 0 && data->executables[index]->type != PIPE)
		index--;
	if (index > 0 && data->executables[index]->type == PIPE)
		index++;
	i_start = index;
	while (data->executables[index] && data->executables[index]->type != PIPE)
	{
		if (data->executables[index]->type == REDIRECTOR)
			size++;
		index++;
	}
	redirections = malloc(sizeof(t_redirector *) * (size + 1));
	if (!redirections)
		fatal_error(data, "malloc");
	redirections[size] = NULL;
	redir_fill(data, redirections, i_start);
	command->redirections = redirections;
}
