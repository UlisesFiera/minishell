/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:28:28 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/17 10:28:28 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner(t_gen_data *data)
{
	printf("\033[33m");
	printf("|------------------------------------------------|\n");
	printf("|                                                |\n");
	printf("| Hello, %s                                    |\n", 
		data->username);
	printf("|                                                |\n");
	printf("| Welcome to ulfernan and alvaro's               |\n");
	printf("|                                                |\n");
	printf("|    *                                           |\n");
	printf("|  (  `                         )       (   (    |\n");
	printf("|  )\\))(   (         (       ( /(    (  )\\  )\\   |\n");
	printf("| ((_)()\\  )\\   (    )\\  (   )\\())  ))\\((_)((_)  |\n");
	printf("| (_()((_)((_)  )\\ )((_) )\\ ((_)\\  /((_)_   _    |\n");
	printf("| |  \\/  | (_) _(_/( (_)((_)| |(_)(_)) | | | |   |\n");
	printf("| | |\\/| | | || ' \\))| |(_-<| ' \\ / -_)| | | |   |\n");
	printf("| |_|  |_| |_||_||_| |_|/__/|_||_|\\___||_| |_|   |\n");
	printf("|                                                |\n");
	printf("|------------------------------------------------|\n");
	printf("\033[0m");
}

void	welcome_message(t_gen_data *data)
{
	print_banner(data);
}