/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/04/08 18:48:31 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	treat_input(t_data *data)			// echo "'jorge' ale"
{	
	//validate input()											
	treat_input_chars(data); 						// echo "'jorge'1ale"  - > se entre as aspas tiver ' ' ou > ou  < ou |, substitui por um char não imprimível
	data->tokens = ft_split(data->input, ' '); 		// echo\0 "'jorge'1ale"\0 	->quebra os inputs em tokens para tratar, o que estiver entre aspas será um token único: "'jorge'1ale"
	treat_token_strings(data);						//	coloca tokens em variável temporária dentro de nova struct | trata quotes-dollar-no quotes-reverse_input_chars
	// data->input = restore_command_line(data->tokens);
}

void	treat_input_chars(t_data *data)
{
	treat_char(data, ' ', 1);
	treat_char(data, '>', 1);
	treat_char(data, '<', 1);
	treat_char(data, '|', 1);	
}

void	treat_char(t_data *data, char c, int number)
{
	int	i;
	int	sign;

	i = 0;
	while (data->input)
	{
		if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			sign = data->input[i];
			i++;
			while (data->input[i] != sign && data->input[i])
			{
				if (data->input[i] == c)
					data->input[i] = number;
				i++;				
			}
		}
		i++;
	}
}

void	treat_token_strings(t_data *data)
{	
	// check_input() | checa se é builtin, operador, comando

	while (data->tokens)
	{
		treat_quotes(data->tokens);
		// treat_dollar;
		no_quotes(data->tokens);
		reverse_input_chars(data->tokens);
	}	
}
