/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:17:22 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/23 18:17:22 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strinsert(char *string, char *insert, int index, int skip)
{
	char	*new_string;
	int		i;
	int		j;
	int		n;

	new_string = malloc(ft_strlen(string) + ft_strlen(insert) - skip + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	j = 0;
	n = 0;
	while (i < index)
		new_string[n++] = string[i++];
	while (insert[j])
		new_string[n++] = insert[j++];
	i = index + skip;
	while (string[i])
		new_string[n++] = string[i++];
	new_string[n] = '\0';
	return (new_string);
}
