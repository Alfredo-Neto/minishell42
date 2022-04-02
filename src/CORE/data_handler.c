/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/02 13:31:32 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{	
	data->input = NULL;
	data->cmds_piped = NULL;
	data->argve = NULL; //(cmd + args)
	data->envp = NULL;
	data->number_of_pipes = -1;
	data->exec_flag = -1;
}

void	data_clean(t_data *data)
{
	free(data->input);
	data->input = NULL;
	free_cmds_piped(data);
	free_argve(data);	
	data->number_of_pipes = -1;
	data->exec_flag = -1;
}

void free_cmds_piped(t_data *data)
{
	int index;

	index = 0;
	if (data->cmds_piped)
	{
		while(data->cmds_piped[index])
		{
			free(data->cmds_piped[index]);
			data->cmds_piped[index] = NULL;
			index++;
		}
		free(data->cmds_piped);
		data->cmds_piped = NULL;
	}
}

void free_argve(t_data *data) //Uso: passar endereço da ***str
{
	int index_block;
	int index_cmd;

	index_block = 0;
	index_cmd = 0;
	if (data->argve)
	{
		while (data->argve[index_block])
		{
			//libera cada bloco(cada processo)
			while(data->argve[index_block][index_cmd])
			{
				free(data->argve[index_block][index_cmd]);
				data->argve[index_block][index_cmd] = NULL;
				index_cmd++;
			}
			free(data->argve[index_block]);
			index_block++;
		
		}
		free(data->argve);
		data->argve = NULL;
	}	    
} 


