/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/11 13:37:22 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../minishell.h"

void	init_shell(void)
{
	char	*username;

	clear();
	printf("\n\n******************");
	printf("\n\t****MY SHELL****");
	printf("\n\n*******************");
	username = getenv("USER");
	printf("\n\n\nUSER is: @%s\n", username);
	sleep(2);
	clear();
}

int	main(void)
{
	char	input_string[MAXCOM];
	char	*parsed_args[MAXLIST];
	char	*parsed_args_piped[MAXLIST];
	int		exec_flag;

	exec_flag = 0;
	init_shell();
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		printf("INPUT %s\n", input_string);
		exec_flag = process_string(input_string, parsed_args,
				parsed_args_piped);
		if (exec_flag == 1)
			exec_args(parsed_args);
		if (exec_flag == 2)
			exec_args_piped(parsed_args, parsed_args_piped);
	}
	return (0);
}
