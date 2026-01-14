/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:51:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/31 00:45:02 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_fields(
	t_gen_data *data, t_token **exp_array, int i_old, int i_new)
{
	char	*var_text;
	int		size;
	int		i;
	int		j;
	int		i_first;

	var_text = ft_strdup(data->executables[i_old]->text);
	if (!var_text)
		fatal_error(data, "malloc");
	i = 0;
	i_first = 0;
	while (var_text[i])
	{
		alloc_token(data, exp_array, i_new, i_old);
		size = field_size(var_text, &i, &i_first);
		exp_array[i_new]->text = ft_calloc(size + 1, sizeof(char));
		if (!exp_array[i_new]->text)
			fatal_error(data, "malloc");
		j = 0;
		while (j < size)
			exp_array[i_new]->text[j++] = var_text[i_first++];
		i_new++;
	}
	free(var_text);
	return (i_new);
}

void	copy_exp_array(t_gen_data *data, t_token **exp_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->expand == 1
			&& data->executables[i]->quote != SINGLE
			&& data->executables[i]->text[0] != '\0')
			j = copy_fields(data, exp_array, i, j);
		else
		{
			exp_array[j] = malloc(sizeof(t_token));
			exp_array[j]->expand = data->executables[i]->expand;
			exp_array[j]->quote = data->executables[i]->quote;
			exp_array[j]->text = ft_strdup(data->executables[i]->text);
			exp_array[j]->type = data->executables[i]->type;
			exp_array[j]->merge = data->executables[i]->merge;
			j++;
		}
		i++;
	}
	free_tokens(data);
	data->executables = exp_array;
}

int	add_tokens(char *var_text)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (var_text[i])
	{
		i = skip_space_tab_nl_field(var_text, i);
		if (var_text[i])
			size++;
		while (var_text[i]
			&& var_text[i] != ' ' && var_text[i] != '\t' && var_text[i] != '\n')
			i++;
	}
	if (size == 1)
		size = 0;
	return (size);
}

void	field_split(t_gen_data *data)
{
	t_token	**exp_array;
	int		size;
	int		i;

	if (data->exit_loop != 0 || g_signal_status != 0)
		return ;
	exp_array = NULL;
	size = data->exec_count;
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->expand == 1
			&& data->executables[i]->quote != SINGLE)
			size += add_tokens(data->executables[i]->text);
		i++;
	}
	exp_array = ft_calloc(size + 1, sizeof(t_token *));
	if (!exp_array)
		fatal_error(data, "malloc");
	exp_array[size] = NULL;
	data->exp_token_size = size;
	copy_exp_array(data, exp_array);
	merge_quotes(data, exp_array);
}
