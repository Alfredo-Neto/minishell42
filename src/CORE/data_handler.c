/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/19 22:58:57 by vlima-nu         ###   ########.fr       */
=======
/*   Updated: 2022/04/20 01:04:03 by azamario         ###   ########.fr       */
>>>>>>> edd043344139372f4985b533fce33c99b2e1eac3
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{	
	ft_bzero(data, sizeof(t_data));
	init_command_path(data);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
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
<<<<<<< HEAD
	free(data->input);
	data->input = NULL;
	free_cmds_piped(data);
	free_argve(data);

	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;

	data->file = NULL; //implemetar free data file
	data->file_mode = NULL; //implemetar free data file mode	
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
=======
	free_str(&data->input);
//	free_str(&data->string); // não foi malocado
//	free_double_str(&data->tokens);
	free_triple_str(&data->argve);
	data->number_of_pipes = -1;
	data->exec_flag = -1;
>>>>>>> edd043344139372f4985b533fce33c99b2e1eac3
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


