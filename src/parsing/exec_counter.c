/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:17:57 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/21 09:17:57 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space_tab_nl_field(char *var_text, int index)
{
	while (var_text[index]
		&& (var_text[index] == ' ' || var_text[index] == '\t'
			|| var_text[index] == '\n'))
		index++;
	return (index);
}

int	skip_space_tab_nl(t_gen_data *data, int index)
{
	while (data->input[index]
		&& (data->input[index] == ' ' || data->input[index] == '\t'
			|| data->input[index] == '\n'))
		index++;
	return (index);
}

int	skip_separators(t_gen_data *data, int index)
{
	data->exec_count++;
	index++;
	if (data->input[index] && data->input[index - 1] != '|'
		&& (data->input[index] == '<' || data->input[index] == '>'))
		index++;
	return (index);
}

int	skip_token(t_gen_data *data, int index)
{
	char	*symbol;

	symbol = " \t\n<>|'\"";
	data->exec_count++;
	while (data->input[index] && (data->input[index] != ' '
			&& ft_strchr(symbol, data->input[index]) == NULL))
		index++;
	return (index);
}

void	exec_counter(t_gen_data *data)
{
	int		i;

	i = 0;
	while (data->input[i])
	{
		i = skip_space_tab_nl(data, i);
		if (data->input[i] == '\0')
			return ;
		if (data->input[i] == '\'' || data->input[i] == '"')
		{
			data->exec_count++;
			i = find_closing_quote(data, i);
			if (i == -1)
				return ;
			i++;
		}
		else if (data->input[i] == '<' || data->input[i] == '>'
			|| data->input[i] == '|')
			i = skip_separators(data, i);
		else
			i = skip_token(data, i);
	}
}
