/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/21 16:54:59 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create an aux **str based on pipe
void pull_pipe(t_data *data) //, char ***cmds_piped)
{
	printf("\n\n%s\n\n", data->input);
	data->cmds_piped = ft_split(data->input, '|');
	if (data->cmds_piped == NULL)
	{
		perror("Malloc failure 1");
		exit_minishell(data, FAILURE);
	}
	if (data->cmds_piped[0] && data->cmds_piped[1] == NULL) 
		data->number_of_pipes = 0;
	else
		data->number_of_pipes = ft_str_count(data->cmds_piped) - 1;
}

//Aqui ganha o formato da estrutura argve - Por isso n retorna, mexe direto na struct
void pull_space(t_data *data) //, char ***cmds_piped)
{
	int i;
	int no_cmds;
	
	i = 0;
	no_cmds = data->number_of_pipes + 1;
	data->argve = (char ***)malloc((no_cmds + 1)* sizeof(char **));
	if (data->argve == NULL)
	{
		perror("Malloc failure 2");
		exit_minishell(data, FAILURE);
	}	
	while((data->cmds_piped)[i])
	{
		data->argve[i] = ft_split((data->cmds_piped)[i], ' ');//leak
		if (data->argve[i] == NULL)
		{
			perror("Malloc failure 3");
			exit_minishell(data, FAILURE);
		} 
		i++;
	}
	data->argve[i] = NULL;
	data->exec_flag = 1;
}	

/*
	// debug: printar as variáveis do pull_space
	i = 0;
	int j;
	while (data->argve[i])
	{
		j = 0;
		printf("\n");
		while(data->argve[i][j])
		{
			printf("...........LEXED %d: %s\n", i, data->argve[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	//fim print variable------------------------------------------------------------------
}	
*/

void lexer (t_data *data)
{
	treat_input(data); 	// devolver linha de comando tratada (aspas) para pull_pipe	| devolve como data->string
	pull_pipe(data); //, &cmds_piped); //tenho estrutura de str** - cada string com linha de cmd
	pull_space(data); //, &cmds_piped); //tenho estrutura de str*** - cada str é um arg(ou cmd)
}
