/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/20 17:44:21 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_minishell(t_data *data, int status)
{	
	data_clean(data);
	double_free(&data->command_path);
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
