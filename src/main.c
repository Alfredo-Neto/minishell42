/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/09 22:41:54 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.
*/
#include "../includes/minishell.h"

int	main(void)
{
	char	inputString[MAXCOM];
	char*	parsedArgs[MAXLIST];
	char*	parsedArgsPiped[MAXLIST];
	int		execFlag;

	execFlag = 0;	
	init_shell();
  	while (1)
	{
		printDir();
		if (takeInput(inputString))
    		continue ;
		printf("INPUT %s\n", inputString);
		execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
		if (execFlag == 1)
			execArgs(parsedArgs);
		if (execFlag == 2)
			execArgsPiped(parsedArgs, parsedArgsPiped);
	}
	return (0);
}
