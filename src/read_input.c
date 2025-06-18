/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/18 17:06:32 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_secondary_prompt = 0;

void	prompt_for_quotes(t_gen_data *data, char quote)
{
	char	*prompt;
	char	*old_input;
	char	*new_input;
	char	*final_input;

	final_input = "";
	if (quote == '\'')
		prompt = "squote> ";
	else
		prompt = "dquote> ";
	while (final_input[ft_strlen(final_input) - 1] != quote)
	{
		old_input = ft_strjoin(data->input, "\n");
		new_input = read_input(data, prompt, 0);
		final_input = ft_strjoin(old_input, new_input);
		free(data->input);
		free(old_input);
		data->input = final_input;
	}
}

void	prompt_for_pipes(t_gen_data *data)
{
	char	*old_input;
	char	*new_input;
	char	*final_input;

	old_input = ft_strjoin(data->input, " ");
	new_input = read_input(data, "pipe> ", 1);
	final_input = ft_strjoin(old_input, new_input);
	free(data->input);
	data->input = final_input;
}

void	check_secondary_prompt(t_gen_data *data)
{
	int	i;

	if (!data->input)
		return ;
	i = 0;
	while (data->input[i])
		i++;
	if (i == 0)
		return ;
	if (data->input[i - 1] == '|' && data->input[i] == '\0')
	{
		in_secondary_prompt = 1;
		prompt_for_pipes(data);
		return ;
	}
	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'' || data->input[i] == '"')
		{
			if (odd_quotes(data->input, i))
			{
				in_secondary_prompt = 1;
				prompt_for_quotes(data, data->input[i]);
				return ;
			}
		}
		i++;
	}
}

char	*read_input(t_gen_data *data, char *prompt, int check_on)
{
	free(data->input);
	data->input = readline(prompt);
	if (!data->input) // readline returns NULL when the user presses ctrl-D, which terminates the shell
		return (NULL);
	if (data->input && data->input[0] != '\0' 
				&& !ft_is_only_spaces(data->input) && check_on == 1)
		add_history(data->input);
	data->lineno++;
	if (check_on == 1)
		check_secondary_prompt(data);
	return (data->input);
}
