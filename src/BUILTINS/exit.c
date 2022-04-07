/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/07 00:37:22 by ebresser         ###   ########.fr       */
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

void mini_exit (t_data *data) //resolver exit!
{
	if (data->exec_mode == NO_PIPE) //qdo tem pipe n faz nada - testar depois
	{
		data->exit_flag = TRUE; //Setada apenas no pai (single exec)
		printf("\nGoodbye!\n");
		exit_minishell(data, SUCCESS);
	}	
}