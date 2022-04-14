/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/04/14 02:14:37 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	treat_input(t_data *data)			// echo "'jorge' ale"
{	
	//validate input()											
	treat_input_chars(data); 						// echo "'jorge'1ale"  - > se entre as aspas tiver ' ' ou > ou  < ou |, substitui por um char não imprimível
	//treat_operators()								// verifica se tem espaços antes de | e redirects
	data->tokens = ft_split(data->input, ' '); 		// echo\0 "'jorge'1ale"\0 	->quebra os inputs em token para tratar, o que estiver entre aspas será um token único: "'jorge'1ale"
	treat_token_strings(data);						//	coloca token em variável temporária dentro de nova struct | trata quotes-dollar no-quotes reverse_input_chars
	// data->input = restore_command_line(data->token);
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
	while (data->input[i])
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

	while (*data->tokens)
	{
		treat_quotes(*data->tokens);		
		no_quotes(*data->tokens);
		data->tokens++;
	}
	// treat_dollar;
	reverse_input_chars(data);	
}

void	treat_quotes(char *token)
{
	int	i;
	
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] != '\'')
			{
				if (token[i] == '\"')
					token[i] = 2;
				i++;
			}
		}
		if (token[i] == '\"')
		{
			i++;
			while (token[i] != '\"')
			{
				if (token[i] == '\'')
					token[i] = 3;
				i++;
			}
		}
		i++;
	}	
}

 void	no_quotes(char *token)
 {
	int quotes;
	int len;
	char *str;
	int i;
	int j;
	
	quotes = 0;
	len = 0;
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		 	quotes++;
		i++;
	}
	if (quotes != 0)
	{
		len = ft_strlen(token) - quotes + 1;
		str = ft_calloc((len), sizeof(char));
		i = 0;
		while (token[i])
		{
			while (token[i] == '\'' || token[i] == '\"')
				i++;
			str[j++] = token[i];
			if (token[i])
				i++;	
		}			
		token = reverse_quotes_treat(str); //não está colocando na struct
		printf("token tratado: %s\n", token);
		free(str);
	}	
 }

char	*reverse_quotes_treat(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == 3)
		{
			str[i] = '\'';
		}
		else if (str[i] == 2)
		{
			str[i] = '\"';
		}
		i++;
	}
	return (str);
}

