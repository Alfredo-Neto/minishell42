/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:16:34 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 13:50:55 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_builtins(t_data *data)
{
	int i;
	int switcher;
	char *builtin_cmd[4];
	
	i = 0;
	switcher = 0;
	builtin_cmd[0] = "exit";
	builtin_cmd[1] = "cd";
	builtin_cmd[2] = "echo";
	builtin_cmd[3] = "hello";
	while (i < 4)
	{
		if (strcmp(data->argve[0][0], builtin_cmd[i]) == 0)
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


void exec_selector(t_data *data)
{
	int builtin;

	builtin = is_builtins(data);
	if (builtin)
		builtin_exec(data, builtin);
	else
		system_exec(data);


	//só para printar:--------------------------------------------------rerirar
	if (builtin)
		printf("                                      BUILTIN (yes)\n");
	else
		printf("                                      BUILTIN (no)");
	//----------------------------------------------------------------
	
}

void system_exec(t_data *data)
{
	if (data->no_pipes)
		multiple_exec(data);
	else
		single_exec(data);
}

