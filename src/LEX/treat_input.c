/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/04/29 16:50:15 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	treat_input(t_data *data)
{
	treat_input_chars(data); // se entre as aspas tiver ' ' ou > ou  < ou |, substitui por um char não imprimível echo "'jorge1ale"\0
	data->tokens = ft_split(data->input, ' '); // quebra os inputs em token para tratar, o que estiver entre aspas será um token único: echo\0 "'jorge1ale"\0
	treat_token_strings(data); // trata os tokens e restabelece a string no data->string || aqui tratamos dollar?
}

void	treat_input_chars(t_data *data)
{
	treat_char(data, ' ', 1);
	treat_char(data, '|', 6);
	treat_char(data, '>', 4);
	treat_char(data, '<', 5);
	treat_char(data, '$', 7);
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
			sign = data->input[i++];
			while (data->input[i] != sign && data->input[i])
			{
				if (data->input[i] == c)
					if ((c == '$' && sign == '\'') || c != '$')
						data->input[i] = number;
				i++;
			}
		}
		i++;
	}
}

void	treat_token_strings(t_data *data)
{
	char	*buf;
	int		i;

	i = 0;
	while (data->tokens[i])
	{
		treat_quotes(data->tokens[i]);	//substitui as aspas internas por 2 ou 3: echo\0 "3jorge31ale"\0
		no_quotes(data->tokens[i]);		//retira as aspas: 3jorge31ale\0 e depois reverte aspas escondidas: 'jorge'1ale\0
		reverse_char(data->tokens[i], 1, ' ');	//reverte os outros caracteres escondidos: 'jorge' ale\0
		if (!data->string)
			data->string = tokens_to_string(data->string, data->tokens[i]);
		else
		{
			buf = tokens_to_string(data->string, data->tokens[i]); // echo\0 "jorge | ale"\0
			free(data->string);
			data->string = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
	free(data->input);
	data->input = ft_strdup(data->string);
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

void	no_quotes(char *token) //echo\0 "3jorge31ale"\0
{
	int		quotes;
	char	*string;
	int		i;
	int		j;

	quotes = 0;
	i = -1;
	while (token[++i])
		if (token[i] == '\'' || token[i] == '\"')
			quotes++;
	if (!quotes)
		return ;
	string = ft_calloc((ft_strlen(token) - quotes + 1), sizeof(char));
	i = 0;
	j = 0;
	while (token[i]) //"3jorge31ale"\0
	{
		while (token[i] == '\'' || token[i] == '\"')
			i++;
		string[j++] = token[i];
		if (token[i])
			i++;
	}
	string = reverse_quotes_treat(string);
	ft_strlcpy(token, string, ft_strlen(string) + 1);
	free(string);
}
