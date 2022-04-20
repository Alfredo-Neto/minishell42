/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/13 17:38:28 by ocarlos-         ###   ########.fr       */
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
	data.envp = envp;
	init_data(&data);
	welcome();
	while (TRUE)
		minishell(&data);
	exit_minishell(&data, SUCCESS);
}


/// envp
// mesclar com developer
// adicionar o envp na lista ligada
// realocar o envp quando essa for alterada