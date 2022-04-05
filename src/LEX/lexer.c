/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/05 02:27:18 by coder            ###   ########.fr       */
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

/*
	Caminho que estamos fazendo em quatro fases:
	1 - pegar a linha de comando e separar pelos espaços: ->	look_for_quotes_and_split()
	2 - retirar as aspas: ->									remove_token_quotes()
	3 - juntar tudo de novo: ->									join_treated_line()
	4 - entregar para a pull_pipe(data)
*/
void lexer (t_data *data)
{
	char	**cmds_piped;
	char	**line;
	char	**line1;

	//aqui a fase 1
	line = look_for_quotes_and_split(data);
	
	//testando o output da fase 1
	while (*line != NULL)
	{
		printf("look_for_quotes_and_split: %s\n", *line);
		line++;
	}	
	
	//printf("aqui\n");
	//aqui a fase 2:
	line1 = remove_token_quotes(line);
	
	//testando output fase 2:
	//printf("aqui 2\n");
	while (*line1 != NULL)
	{
		printf("remove_token_quotes: %s\n", *line1);
		line1++;
	}	
	
	//aqui a fase 3:
	//join_treated_line(line1)
	
	//aqui a fase 4:
	cmds_piped = pull_pipe(data); // Conta pipes, retorna array com ponteiros para string ou a linha de comando		
	pull_space(data, cmds_piped); // Cria tokens utilizando espaço como delimitador
	free_double_str(&cmds_piped);
}

// echo  "ale | jorge"
//	echo ale | jorge 

/*	linha de comando:	ls -l | wc -l
	pull_pipe retorna:	ls -l\0 wc -l\0 
	pull space retorna:	ls\0 -l\0 wc\0 -l\0 (coloca no argve)

	linha de comando:	echo "'jorge' ale marce"
	pull_pipe retorna: 	echo "'jorge' ale marce"\0 NULL
	pull_space retorna: echo\0 "'jorge'\0 ale\0 marce"\0 -> vamos tratar as aspas antes de entregar o argumento para a pull_space
*/

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
			printf("......................LEXED %d: %s\n", i, data->argve[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
*/
