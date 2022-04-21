/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/04/21 19:46:42 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	treat_input(t_data *data)			// echo "'jorge' ale"
{	
	//validate input()											
	treat_input_chars(data); 						// se entre as aspas tiver ' ' ou > ou  < ou |, substitui por um char não imprimível echo "'jorge1ale"\0
	//treat_operators()								// verifica se tem espaços antes de | e redirects
	data->tokens = ft_split(data->input, ' '); 		// quebra os inputs em token para tratar, o que estiver entre aspas será um token único: echo\0 "'jorge1ale"\0
	treat_token_strings(data);						// trata os tokens e restabelece a string no data->string || aqui tratamos dollar?
	pull_pipe(data);
}

void	treat_input_chars(t_data *data)
{
	treat_char(data, ' ', 1);
	treat_char(data, '>', 4);
	treat_char(data, '<', 5);
	treat_char(data, '|', 6);
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

void	treat_token_strings(t_data *data) //echo\0 "'jorge1ale"\0
{
	char	*buf;
	int		i;

	// check_input() | checa se é builtin, operador, comando
	i = 0;
	while (data->tokens[i])
	{
		treat_quotes(data->tokens[i]); 	//substitui as aspas internas por 2 ou 3: echo\0 "3jorge31ale"\0
		no_quotes(data->tokens[i]);		//retira as aspas: 3jorge31ale\0 e depois reverte aspas escondidas: 'jorge'1ale\0
		reverse_input_chars(data->tokens[i]); //reverte os outros caracteres escondidos: 'jorge' ale\0
		// printf("data->tokens %s\n", data->tokens[i]);
		if (!data->string)
			data->string = tokens_to_string(data->string, data->tokens[i]); // echo 'jorge' ale\0
		else
		{
			buf = tokens_to_string(data->string, data->tokens[i]); // echo\0 "jorge | ale"\0
			free(data->string);
			data->string = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
	// printf("data->input %s\n", data->input);
	// printf("data->string %s\n", data->string);
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
	int		len;
	char	*string;
	int		i;
	int		j;
	
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
		string = ft_calloc((len), sizeof(char));
		i = 0;
		while (token[i]) //"3jorge31ale"\0
		{
			while (token[i] == '\'' || token[i] == '\"')
				i++;
			string[j++] = token[i];
			if (token[i])
				i++;	
		}			
		string = reverse_quotes_treat(string); //reverte as aspas
		// printf("data->tokens: %s\n", token);
		// printf("token tratado: %s\n", string);
		i = 0;
		while (string[i])
		{
			token[i] = string[i];
			i++;
		}
		token[i] = '\0';
		// printf("entrou no data->tokens %s\n", token);
		free(string);
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

void	reverse_input_chars(char *token) // echo\0 23jorge31ale2\0
{
	reverse_char(token, 1, ' ');
	reverse_char(token, 4, '>');
	reverse_char(token, 5, '<');
	reverse_char(token, 6, '|');
	reverse_char(token, 7, '$');
}

void	reverse_char(char *cmd, int nbr, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == nbr)
			cmd[i] = c;
		i++;
	}
}

char	*tokens_to_string(char const *s1, char const *s2)
{
	char		*string;
	int			space;
	size_t		i;
	size_t		j;

	i = 0;
	space = ft_strlen(s1) != 0;
	string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1 + space) * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			string[i] = s1[i];
			i++;
		}
		string[i++] = ' ';
	}
	j = 0;
	while (s2[j])
	{
		string[i + j] = s2[j];
		j++;
	}
	string[i + j] = '\0';
	return (string);
}
