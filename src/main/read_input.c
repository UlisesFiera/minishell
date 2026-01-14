/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/30 20:41:41 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unclosed_quotes(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'')
		{
			if (odd_quotes(data->input, i))
			{
				unclosed_token_error("'", data);
				return ;
			}
		}
		else if (data->input[i] == '"')
		{
			if (odd_quotes(data->input, i))
			{
				unclosed_token_error("\"", data);
				return ;
			}
		}
		i++;
	}
}

void	check_unclosed_pipes(t_gen_data *data)
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
		unclosed_token_error("|", data);
		return ;
	}
	if (data->input[i] == '|' && i == 0)
	{
		syntax_error("|", data, 3);
		return ;
	}
}

void	read_input(t_gen_data *data, char *prompt, int check_on)
{
	if (data->input)
		free(data->input);
	data->input = readline(prompt);
	if (!data->input)
		return ;
	if (data->input && data->input[0] != '\0'
		&& !ft_is_only_spaces(data->input) && check_on == 1)
		add_history(data->input);
	data->lineno++;
	if (check_on == 1)
	{
		check_unclosed_pipes(data);
		check_unclosed_quotes(data);
	}
}
