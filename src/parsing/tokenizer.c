/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:39:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/31 00:28:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	generic_token(t_gen_data *data, t_token *token, int *index)
{
	char	*symbol;
	int		start_i;
	int		i;

	symbol = " \t\n<>|'\"";
	start_i = *index;
	while (data->input[*index]
		&& ft_strchr(symbol, data->input[*index]) == NULL)
	{
		if (data->input[*index] == '$')
			token->expand = 1;
		(*index)++;
	}
	token->text = malloc(*index - start_i + 1);
	if (!token->text)
		fatal_error(data, "malloc");
	i = 0;
	while (start_i < *index)
		token->text[i++] = data->input[start_i++];
	token->text[i] = '\0';
	symbol = " \t\n<>|";
	if (data->input[*index]
		&& ft_strchr(symbol, data->input[*index]) == NULL)
		token->merge = 1;
}

void	redirector_token(t_gen_data *data, t_token *token, int *index)
{
	token->type = REDIRECTOR;
	data->redir_count++;
	if (data->input[*index] && data->input[*index] != '|'
		&& (data->input[*index + 1] == data->input[*index]))
	{
		token->text = malloc(3);
		if (!token->text)
			fatal_error(data, "malloc");
		token->text[0] = data->input[*index];
		token->text[1] = data->input[*index];
		token->text[2] = '\0';
		*index += 2;
		return ;
	}
	token->text = malloc(2);
	if (!token->text)
		fatal_error(data, "malloc");
	token->text[0] = data->input[*index];
	token->text[1] = '\0';
	(*index)++;
}

void	quoted_token(t_gen_data *data, t_token *token, int *index)
{
	int	size;
	int	start_i;
	int	i;

	size = 0;
	if (data->input[*index] == '\'')
		token->quote = SINGLE;
	if (data->input[*index] == '"')
		token->quote = DOUBLE;
	start_i = *index;
	*index = find_closing_quote(data, *index);
	size = (*index - start_i) - 1;
	token->text = malloc(size + 1);
	if (!token->text)
		fatal_error(data, "malloc");
	token->text[size] = '\0';
	start_i++;
	i = 0;
	while (start_i < *index)
	{
		if (data->input[start_i] == '$' && token->quote == DOUBLE)
			token->expand = 1;
		token->text[i++] = data->input[start_i++];
	}
	(*index)++;
}

t_token	*fill_token(t_gen_data *data, int *index, t_token *token)
{
	char	*symbol;

	symbol = " \t\n<>|";
	token->type = WORD;
	token->expand = 0;
	token->quote = NONE;
	token->merge = 0;
	*index = skip_space_tab_nl(data, *index);
	if (data->input[*index] == '\'' || data->input[*index] == '"')
	{
		quoted_token(data, token, index);
		if (data->input[*index]
			&& ft_strchr(symbol, data->input[*index]) == NULL)
			token->merge = 1;
	}
	else if (data->input[*index] == '<' || data->input[*index] == '>'
		|| data->input[*index] == '|')
		redirector_token(data, token, index);
	else
		generic_token(data, token, index);
	return (token);
}

t_token	*exec_split(t_gen_data *data)
{
	int			i;
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
		fatal_error(data, "malloc");
	i = data->token_index;
	token = fill_token(data, &i, token);
	data->token_index = i;
	return (token);
}
