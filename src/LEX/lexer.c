/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/14 02:07:03 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*	Create an aux **str based on pipe
   	Conta pipes, retorna array com ponteiros para strings cortadas por pipes
	Caso não existam pipes, retorna o imput da linha de comando + NULL no segundo ponteiro */
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
		data->number_of_pipes = 0;
	else
		data->number_of_pipes = ft_str_count(input_piped) - 1;	
	return (input_piped);
}

/*	Aqui ganha o formato da estrutura argve - Por isso n retorna, mexe direto na struct
	Cria novos tokens utilizando espaço como delimitador e coloca dentro do argve */
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
		data->argve[i] = ft_split(cmds_piped[i], ' ');
		if (data->argve[i] == NULL)
		{
			perror("Malloc failure");
			free_double_str(&cmds_piped);
			exit_minishell(data, FAILURE);
		} 
		i++;
	}
	data->argve[i] = NULL;
	data->exec_flag = 1;
}	

void lexer (t_data *data)
{
	char	**cmds_piped;

	treat_input(data); 			// devolver linha de comando tratada (aspas) para pull_pipe

	cmds_piped = pull_pipe(data); // Conta pipes, retorna array com ponteiros para string ou a linha de comando		
	pull_space(data, cmds_piped); // Cria tokens utilizando espaço como delimitador
	free_double_str(&cmds_piped);
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
*/
