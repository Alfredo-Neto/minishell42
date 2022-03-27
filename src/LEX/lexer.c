/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/27 16:13:48 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create an aux **str based on pipe
void pull_pipe(t_data *data, char ***cmds_piped)
{
	if (!data->input)
		printf("Input NULO\n");
	*cmds_piped = ft_split(data->input, '|');
	if (*cmds_piped == NULL)
	{
		perror("Malloc failure");
		exit_minishell(data, FAILURE);
	} 
	if ((*cmds_piped)[0] && (*cmds_piped)[1] == NULL) 
		data->number_of_pipes = 0;
	else
		data->number_of_pipes = ft_str_count((*cmds_piped)) - 1;
}

//Aqui ganha o formato da estrutura argve - Por isso n retorna, mexe direto na struct
void pull_space(t_data *data, char **cmds_piped)
{
	int i;
	int no_cmds;
	
	i = 0;
	no_cmds = data->number_of_pipes + 1;
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
	
	pull_pipe(data, &cmds_piped); //tenho estrutura de str** - cada string com linha de cmd
	pull_space(data, cmds_piped); //tenho estrutura de str*** - cada str é um arg(ou cmd)
	free_double_str(&cmds_piped);
}