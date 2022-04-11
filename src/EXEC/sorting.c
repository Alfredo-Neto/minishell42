/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:16:34 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/06 21:53:31 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_builtins(char *cmd)
{
	int i;
	int switcher;
	char *builtin_cmd[NUMBER_OF_BUILTINS];
	
	i = 0;
	switcher = 0;
	builtin_cmd[0] = "exit";
	builtin_cmd[1] = "cd";
	builtin_cmd[2] = "echo";
	builtin_cmd[3] = "hello";
	builtin_cmd[4] = "help"; //
	while (i < NUMBER_OF_BUILTINS)
	{
		if (strcmp(cmd, builtin_cmd[i]) == 0)
		{
			switcher = i + 1;
			break;
		}
		i++;
	}
	if(switcher)
		return (switcher);
	return (FALSE);	
}


//void exec_selector(t_data *data)
//{
//	if (data->number_of_pipes)
//		data->exec_mode = WITH_PIPE;
//	else
//		data->exec_mode = NO_PIPE;
//}

	