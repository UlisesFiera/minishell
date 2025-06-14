/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/14 14:58:28 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_for_quotes(t_gen_data *data, char quote, int index)
{
	char	*prompt;
	char	*old_input;
	char	*new_input;
	char	*final_input;

	if (!odd_quotes(data->input, index - 1))
		return ;
	final_input = "";
	if (quote == '\'')
		prompt = "quote> ";
	else
		prompt = "dquote> ";
	while (final_input[ft_strlen(final_input) - 1] != quote)
	{
		old_input = ft_strdup(data->input);
		new_input = read_input(data, prompt, 0);
		final_input = ft_strjoin(old_input, new_input);
		free(data->input);
		data->input = final_input;
	}
}

void	prompt_for_pipes(t_gen_data *data)
{
	char	*space;
	char	*old_input;
	char	*new_input;
	char	*final_input;

	space = " ";
	old_input = ft_strjoin(data->input, space);
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
		prompt_for_pipes(data);
		return ;
	}
	else if ((data->input[i - 1] ==  '\'' || data->input[i - 1] ==  '"')
			&& data->input[i] == '\0' && odd_quotes(data->input, i - 1))
	{
		prompt_for_quotes(data, data->input[i - 1], i);
		return ;
	}
}

char	*read_input(t_gen_data *data, char *prompt, int check_on)
{
	free(data->input);
	data->input = readline(prompt);
	if (check_on == 1)
		check_secondary_prompt(data);
	if (!data->input) // readline returns NULL when the user presses ctrl-D, which terminates the shell
		return (NULL);
	if (data->input && data->input[0] != '\0' 
				&& !ft_is_only_spaces(data->input))
		add_history(data->input);
	return (data->input);
}
