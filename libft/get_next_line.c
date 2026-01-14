/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:55:48 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:29:58 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reset_list(t_list_line **str_list)
{
	t_list_line		*last_node;
	t_list_line		*clean_node;
	char			*clean_str;
	int				i;
	int				j;

	clean_str = malloc(BUFFER_SIZE);
	clean_node = malloc(sizeof(t_list));
	if (!clean_str || !clean_node)
		return ;
	last_node = lstlast(*str_list);
	i = 0;
	j = 0;
	while (last_node->string[i] && last_node->string[i] != '\n')
		i++;
	while (last_node->string[i] && last_node->string[++i])
		clean_str[j++] = last_node->string[i];
	clean_str[j] = '\0';
	clean_node->string = clean_str;
	clean_node->next = NULL;
	dealloc(str_list, clean_node, clean_str);
}

char	*get_line(t_list_line *str_list)
{
	int		len;
	char	*line;

	if (!str_list)
		return (NULL);
	len = len_sum(str_list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	copy_content(str_list, line);
	return (line);
}

void	add_node(t_list_line **str_list, char *str_read)
{
	t_list_line		*last_node;
	t_list_line		*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = lstlast(*str_list);
	if (last_node == NULL)
		*str_list = new_node;
	else
		last_node->next = new_node;
	new_node->string = str_read;
	new_node->next = NULL;
}

void	create_list(t_list_line **str_list, int fd)
{
	int		len;
	char	*str_read;

	while (!found_nl(*str_list))
	{
		str_read = malloc(BUFFER_SIZE + 1);
		if (!str_read)
			return ;
		len = read(fd, str_read, BUFFER_SIZE);
		if (len <= 0)
		{
			free(str_read);
			return ;
		}
		str_read[len] = '\0';
		add_node(str_list, str_read);
	}
}

char	*get_next_line(int fd)
{
	static t_list_line	*str_list;
	char				*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&str_list, fd);
	if (!str_list)
		return (NULL);
	next_line = get_line(str_list);
	reset_list(&str_list);
	return (next_line);
}

/*

-> 	Error checks:
	l-> "fd" less than zero means error; the buffer can't be 
		less than zero (obviously); read can return less than 
		zero in that case if it finds "fd" errors, 
		such as too many "fd" opened, or it being closed,
		or invalid.
->	"create_list", this is where we create the list.
	l->	"size" gives the actual size of the chunk read because 
		we need to add a "\0" at the end and the size can be 
		different from BUFFER_SIZE when we reach a "\n" or an EOF.
	l->	"str_read" is the buffer that stores every chunk read.
	l->	We store each string until we find one that contains 
		the "\n".
	l->	We got our first chunk of characters stored! Now we put 
		them into a node and add the node to the list.
->	"add_node" appends a new node at the end of the list and 
	copies the data read from the upper function into it.
	l-> First we check if we are at the head of the list, in 
	which case, our function "lstlast" returns NULL.
-> "found_nl" is a boolean that scans through the content of
	the nodes and looks for a "\n". If found, returns 1; if 
	not, or error, 0. The NULL check also works for the first 
	iteration where the list is still empty.
->	Now get have a list with each node containing a string. 
	We wanna copy the content of each node into a string, and 
	that's our line.
-> "reset_list" frees the content of every node on the list 
	but keeps the last one with the remaining characters
	after the "\n" so next time the function is called, 
	the content of the first node of the list includes those.
	In the case there were no more characters after "\n" in 
	our node, the list stays initialised in NULL without
	content, and we free the string and clean node that were 
	suppose to hold that information.

*/