/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/13 21:45:52 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_minishell(t_data *data, int status)
{	
	data_clean(data);
	free_command_path(data);
	rl_clear_history();
	exit (status);
}

void check_exit(t_data *data)
{
	int	builtin_flag;
	if (data->number_of_pipes == 0)
	{
		builtin_flag = is_builtins(data->argve[0][0]);
		if (builtin_flag == EXIT) 
			mini_exit(data);
	}
}

void mini_exit (t_data *data) //resolver exit!
{
	if (data->number_of_pipes == 0)
	{
		data->exit_flag = TRUE; //Setada apenas no pai (single exec)
		printf("\nGoodbye!\n");
		exit_minishell(data, SUCCESS);
	}	
}