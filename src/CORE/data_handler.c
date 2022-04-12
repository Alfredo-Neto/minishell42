/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/12 00:04:43 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{	
	data->input = NULL;
	data->cmds_piped = NULL;
	data->argve = NULL; //(cmd + args)
	data->envp = NULL;
	init_command_path(data);
	data->file = NULL;
	data->file_mode = NULL;
	//data->redirect_out_mode = NULL; //DEBUG
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
	//data->exec_mode = GARBAGE;
	data->exit_flag = FALSE;
}

int init_command_path(t_data *data)
{
	int i;
	int ret;

	data->command_path = ft_split(getenv("PATH"), ':');
	i = 0;
	while(data->command_path[i] != NULL)
	{
		ret = ft_strjoin_handled(&(data->command_path[i]), "/");
		if (ret == FAILURE)
		{
			perror("Malloc failed");
			exit_minishell(data, FAILURE);
		}
		i++;
		
	}
	return SUCCESS;
}

void	data_clean(t_data *data)
{
	free(data->input);
	data->input = NULL;
	free_cmds_piped(data);
	free_argve(data);
	//data->infile = NULL;//
	//data->outfile = NULL;//
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
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

void free_command_path(t_data *data)
{
	int index;

	index = 0;
	if (data->command_path)
	{
		while(data->command_path[index])
		{
			free(data->command_path[index]);
			data->command_path[index] = NULL;
			index++;
		}
		free(data->command_path);
		data->command_path = NULL;
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
			index_cmd = 0;
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


