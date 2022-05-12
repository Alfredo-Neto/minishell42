/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/05/12 00:41:15 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void shift_id_cmd(t_data *data, int id, int up_to_token);

// functions for parsing command line
int	parser(t_data *data)
{
	int	i;
	int j;
	int up_to_i;
	int up_to_j;

	i = 0;
	j = 0;
	up_to_i = -1;
	up_to_j = -1;

	data->exec_flag = (char *)ft_calloc(data->number_of_pipes + 1, sizeof(char));
	

	while (data->argve[i])
	{
		while(data->argve[i][j])
		{
			if(grab_vars(data, data->argve[i][j]))
			{
				data->exec_flag[i] = VAR_DEFINITION;
				up_to_i = i;
				up_to_j = j;
			}
			j++;
		}
		if (up_to_i != -1 && up_to_j != -1 && data->argve[up_to_i][up_to_j + 1] != NULL)
		{
			shift_id_cmd(data, up_to_i, up_to_j);
			data->exec_flag[i] = TRUE;
		}			
		i++;
		j = 0;
	}
	//printf("i = %d\nj = %d\n", up_to_i, up_to_j);
	
		
	//debug:
	i = 0;
	j = 0;
	while(data->argve[i])
	{
		while(data->argve[i][j])
		{
			printf("[ %s ]\n", data->argve[i][j]);
			j++;
		}
		i++;
		j = 0;
	}
	//Depois avaliar essa expressao	se cabe aqui	
	if (is_builtins(data->argve[0][0]) == EXPORT)
		data->exec_flag[0] = 1;
	return (SUCCESS);
}

static void shift_id_cmd(t_data *data, int id, int up_to_token)
{
	int token;
	int no_str;
	char **aux;
	int index;
	
	no_str = ft_str_count(data->argve[id]); //4 -> 0 1 2 3
	aux = (char **)malloc(sizeof(char *) * (no_str - up_to_token));
	token = up_to_token + 1;
	index = 0;
	while(data->argve[id][token])
	{
		aux[index] = ft_strdup(data->argve[id][token]);
		free(data->argve[id][token]);
		data->argve[id][token] = NULL;
		token++;
		index++;
	}
	aux[index] = NULL;
	//double_free((void ***)&data->argve[id]);
	free(data->argve[id]);
	data->argve[id] = aux;
}
