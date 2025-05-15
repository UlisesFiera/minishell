/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:56:49 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 16:56:49 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_handler(t_gen_data *data, char *redirection, int index,
							char **env) // index is where the redirect is
{
	if (!ft_strcmp(redirection, "<"))
		exec_from_input(data, env, index);
	else if (!ft_strcmp(redirection, ">"))
		exec_to_output(data, env, index);
	else if (!ft_strcmp(redirection, ">>"))
		exec_append(data, env, index);
	else if (!ft_strcmp(redirection, "<<")) 
		exec_heredoc(data, env, index);
}

int	redirect_check(t_gen_data *data, char **env)
{
	int		i;

	i = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<") 
			|| !ft_strcmp(data->executables[i], ">")
			|| !ft_strcmp(data->executables[i], "<<") 
			|| !ft_strcmp(data->executables[i], ">>"))
		{
			redirect_handler(data, data->executables[i], i, env);
			return (1);
		}
		i++;
	}
	return (0);
}
