/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/20 17:46:49 by vlima-nu         ###   ########.fr       */
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
	if (data->string)
	{
		free(data->string);
		data->string = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	double_free(&data->cmds_piped);
	double_free(&data->tokens);
	free_argve(data);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;

	data->file = NULL; //implemetar free data file
	data->file_mode = NULL; //implemetar free data file mode	
}

void	double_free(char ***ptr)
{
	int		i;

	i = 0;
	if (!*ptr)
		return ;
	while ((*ptr)[i])
	{
		if ((*ptr)[i])
			free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

void	free_argve(t_data *data) //Uso: passar endereço da ***str
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


