/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:41:13 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 21:41:13 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_merge_str_loop(
			t_gen_data *data, t_token **exp_array, int i_start, int size)
{
	char	*merge_str;
	int		n;
	int		j;

	merge_str = ft_calloc(size + 1, 1);
	if (!merge_str)
		fatal_error(data, "malloc");
	n = 0;
	while (exp_array[i_start])
	{
		j = 0;
		while (exp_array[i_start]->text && exp_array[i_start]->text[j])
			merge_str[n++] = exp_array[i_start]->text[j++];
		if (exp_array[i_start]->merge == 0)
			return (merge_str);
		i_start++;
	}
	return (merge_str);
}

char	*copy_merge_str(t_gen_data *data, t_token **exp_array, int *i)
{
	int		j;
	int		i_start;
	int		size;

	i_start = *i;
	size = 0;
	while (exp_array[*i])
	{
		j = 0;
		while (exp_array[*i]->text && exp_array[*i]->text[j])
		{
			size++;
			j++;
		}
		if (exp_array[*i]->merge == 0)
		{
			(*i)++;
			return (copy_merge_str_loop(data, exp_array, i_start, size));
		}
		(*i)++;
	}
	return (copy_merge_str_loop(data, exp_array, i_start, size));
}

void	copy_merge_fields(
	t_gen_data *data, t_token **exp_array, t_token **merge_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exp_array[i])
	{
		merge_array[j] = ft_calloc(1, sizeof(t_token));
		if (exp_array[i]->merge == 1)
		{
			merge_array[j]->expand = exp_array[i]->expand;
			merge_array[j]->quote = exp_array[i]->quote;
			merge_array[j]->type = exp_array[i]->type;
			merge_array[j]->text = copy_merge_str(data, exp_array, &i);
		}
		else
		{
			merge_array[j]->expand = exp_array[i]->expand;
			merge_array[j]->quote = exp_array[i]->quote;
			merge_array[j]->type = exp_array[i]->type;
			merge_array[j]->text = ft_strdup(exp_array[i]->text);
			i++;
		}
		j++;
	}
}

int	merge_size(t_token **exp_array)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (exp_array[i])
	{
		if (exp_array[i]->merge == 1)
		{
			while (exp_array[i] && exp_array[i]->merge == 1)
				i++;
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

void	merge_quotes(t_gen_data *data, t_token **exp_array)
{
	t_token	**merge_array;
	int		size;

	size = merge_size(exp_array);
	if (size == data->exp_token_size || size == 0)
		return ;
	merge_array = ft_calloc(size + 1, sizeof(t_token *));
	if (!merge_array)
		fatal_error(data, "malloc");
	copy_merge_fields(data, exp_array, merge_array);
	free_tokens(data);
	data->executables = merge_array;
}
