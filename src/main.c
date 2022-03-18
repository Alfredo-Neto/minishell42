/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/18 17:23:50 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../minishell.h"

void	welcome(void)
{
	char	*username;

	clear();
	username = getenv("USER");
	printf("\n\n\nHi, @%s!\n", username);
	sleep(1);
	clear();
}

void	init_data(t_data *data)
{
	data->input_string[0] = '\0';
	data->parsed_args[0] = NULL;
	data->parsed_args_piped[0] = NULL;
	data->exec_flag = 0;
	// adicionar init_data...
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	(void)argc;
	(void)argv;
	init_data(&data);
	welcome();
	data.env_variable = envp;
	while (1)
		minishell(&data);
	return (0);
}
