/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:16:34 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/21 18:32:55 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
int is_builtins(t_data *data)
{
	int i;
	int switch_own_arg;
	char *list_of_own_cmds[4];
	char *username;

	i = 0;
	switch_own_arg = 0;
	list_of_own_cmds[0] = "exit";
	list_of_own_cmds[1] = "cd";
	list_of_own_cmds[2] = "echo";
	list_of_own_cmds[3] = "hello";
	while (i < 4)
	{
		if (strcmp(data->argve[0][0], list_of_own_cmds[i]) == 0)
		{
			switch_own_arg = i + 1;
			break;
		}
		i++;
	}
	if (switch_own_arg)
		return (switch_own_arg);
	return (FALSE);	
}


int sorting_executor(t_data *data) 
{
	int sort;

	sort = is_builtins(data->argve);
	if (sort)
		switch_builtin(data, sort);
	else
	{
		if (data->no_pipes)
			multiple_exec(data);
		else
			single_exec(data);
	}

	//só para printar:--------------------------------------------------rerirar
	if (sort)
		printf("                                      BUILTIN (yes)\n");
	else
		printf("                                      BUILTIN (no)");
	//----------------------------------------------------------------
}
