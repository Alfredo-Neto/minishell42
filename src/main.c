/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/22 22:51:13 by joeduard         ###   ########.fr       */
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
	static char	*username;

	clear();
	username = getenv("USER");
	printf("|			        			|\n");
	printf("|			MINISHELL			|\n");
	printf("|			        			|\n");
	printf("\n\n\nHi, @%s!\n\n", username);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	(void)argc;
	(void)argv;
	init_data(&data);
	welcome();
	data.envp = envp;
	while (TRUE)
		minishell(&data);
	exit_minishell(&data, SUCCESS);
}
