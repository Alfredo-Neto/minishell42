/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 23:20:46 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create an aux **str based on pipe
char **pull_pipe(t_data *data)
{
	char	**input_piped;	

	if (!data->input)
		printf("Input NULO\n");
	input_piped = ft_split(data->input, '|');
	if (input_piped == NULL)
	{
		perror("Malloc failure");
		exit_minishell(data, FAILURE);
	} 
	if (input_piped[0] && input_piped[1] == NULL) 
		data->no_pipes = 0;
	else
		data->no_pipes = ft_str_count(input_piped) - 1;	
	return (input_piped);
}

//Aqui ganha o formato da estrutura argve - Por isso n retorna, mexe direto na struct
void pull_space(t_data *data, char **cmds_piped)
{
	int i;
	int no_cmds;
	
	i = 0;
	no_cmds = data->no_pipes + 1;
	data->argve = (char ***)malloc((no_cmds + 1)* sizeof(char **));
	if (data->argve == NULL)
	{
		perror("Malloc failure");
		free_double_str(&cmds_piped);
		exit_minishell(data, FAILURE);
	}	
	while(cmds_piped[i])
	{
		data->argve[i] = ft_split(cmds_piped[i], ' ');//leak
		if (data->argve[i] == NULL)
		{
			perror("Malloc failure");
			free_double_str(&cmds_piped);
			exit_minishell(data, FAILURE);
		} 
		i++;
	}
	data->argve[i] = NULL;

	//FIM
	// print variable ------RETIRAR--------------------------------------------------------
	i = 0;
	int j;
	while (data->argve[i])
	{
		j = 0;
		printf("\n");
		while(data->argve[i][j])
		{
			printf("......................LEXED %d: %s\n", i, data->argve[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	//fim print variable------------------------------------------------------------------
}	


void lexer (t_data *data)
{
	char	**cmds_piped;
	
	cmds_piped = pull_pipe(data); //tenho estrutura de str** - cada string com linha de cmd
	pull_space(data, cmds_piped); //tenho estrutura de str*** - cada str é um arg(ou cmd)
	free_double_str(&cmds_piped);
}