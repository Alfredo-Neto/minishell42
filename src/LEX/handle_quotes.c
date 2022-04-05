/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:34:34 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/05 02:49:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

int find_quote(char *str)
{
    int i;

    i = 0;
    if (str == 0)
        return (EXIT_FAILURE);
    while (str[i] != '\0')
    {
        if (str[i] == SQUOTES || str[i] == DQUOTES)
            return (i);
        i++;
    }
    return (NO_QUOTES_FOUND);
}

void    mix_quotes(char *from_single_quotes, char *from_double_quotes, char *str)
{
    // char *no_quotes;
   	// int quote_pos;
   	int i;
	int j;

    i = 0;
	j = 1;

    printf("mix_quotes: \n");

    if(from_single_quotes[i] && from_double_quotes[j])
    {
        printf("mix_quotes IF: \n");
        single_quotes(from_single_quotes,str);
    }
    else if(from_double_quotes[i] && from_single_quotes[j])
    {
        printf("mix_quotes ELSE: \n");
        double_quotes(from_double_quotes, str);
    }
} 

void	single_quotes(char *from_single_quotes, char *str)
{
    char *no_quotes;
   	int quote_pos;
   	int i;
	int j;
	
	i = 0;
	j = 0;
	no_quotes = ft_strtrim(from_single_quotes, "\'"); // "'jorge'"
	printf("SINGLE QUOTES - TRIM: %s\n", no_quotes);
    quote_pos = find_quote(str);
    while (str[i])
    {
    	if (str[i] == SQUOTES)
        {
    	    while (no_quotes[j])
			{
                str[quote_pos++] = no_quotes[j++];
			}
        	str[quote_pos] = '\0';
            break;
        }
        i++;
    }
}

void	double_quotes(char *from_double_quotes, char *str)
{
    char *no_quotes;
   	int quote_pos;
	int i;
	int j;
	
	i = 0;
	j = 0;
	no_quotes = ft_strtrim(from_double_quotes, "\"");
    printf("DOUBLE QUOTES - TRIM: %s\n", no_quotes);
    quote_pos = find_quote(str);
    while (str[i])
    {
    	if (str[i] == DQUOTES)
        {
    	    while (no_quotes[j])
			{
                str[quote_pos++] = no_quotes[j++];
			}
        	str[quote_pos] = '\0';
            break;
        }
        i++;
    }	
}

char *handle_quotes(char *str)
{
    char *from_single_quotes;
    char *from_double_quotes;
    if (str)
    {
        from_single_quotes = ft_strchr(str, SQUOTES);
        from_double_quotes = ft_strchr(str, DQUOTES);
        // if(from_single_quotes && from_double_quotes)
        //     mix_quotes(from_single_quotes, from_single_quotes, str);
        if (from_single_quotes)
            single_quotes(from_single_quotes, str);
        else if (from_double_quotes)
			double_quotes(from_double_quotes, str);
        printf("str: %s\n", str);
    }
    return (str);
}

*/

// aqui o código da Marce


// 2
int	count_tokens(t_data *data)
{
	int	i;
	int	space_count;
	int	single_quote_status;
	int	double_quote_status;

	i = -1;
	space_count = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	while (data->input[++i])
	{
		if (data->input[i] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		else if (data->input[i] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (data->input[i] == ' ' && (!single_quote_status && !double_quote_status))
			space_count++;
	}
	data->token_count = space_count + 1;
	return (space_count + 1);
}


// 1
char	**look_for_quotes_and_split(t_data *data) //data->input
{
	int		palavra[3];
	int		single_quote_status;
	int		double_quote_status;
	char	**line_array;

	palavra[0] = -1;
	palavra[1] = 0;
	palavra[2] = 0;
	single_quote_status = OFF;
	double_quote_status = OFF;
	line_array = malloc(sizeof(char *) * (count_tokens(data) + 1));
	line_array[count_tokens(data)] = NULL;
	while (data->input[++palavra[0]])
	{
		if (data->input[palavra[0]] == '\'')
		{
			if (single_quote_status)
				single_quote_status = OFF;
			else if (!single_quote_status && !double_quote_status)
				single_quote_status = ON;
		}
		if (data->input[palavra[0]] == '\"')
		{
			if (double_quote_status)
				double_quote_status = OFF;
			else if (!double_quote_status && !single_quote_status)
				double_quote_status = ON;
		}
		if (data->input[palavra[0]] != ' ' || (data->input[palavra[0]] == ' ' && (single_quote_status || double_quote_status)))
		{
			palavra[1]++;
			// printf("primeiro if\n");
		}
		if (palavra[1] && ((data->input[palavra[0] + 1] == '\0' || (data->input[palavra[0] + 1] == ' ' && (!single_quote_status && !double_quote_status)))))
		{
			line_array[palavra[2]++] = ft_substr(data->input + palavra[0] + 1 - palavra[1], 0, palavra[1]);
			palavra[1] = 0;
			// printf("line_array 2nd if: %s\n", *line_array);
		}
	}
	return (line_array);
}


// 4
void	remove_middle_quotes(char **line, int j)
{
	char    *first_part;
    char    *temp;

    first_part = ft_substr(*line, 0, j);
    temp = ft_strjoin(first_part, *line + j + 1);
    free(*line);
    free(first_part);
    *line = temp;
}

// 3
char 	**remove_token_quotes(char **line)   // echo "jorge"
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		printf("dentro do while da rtq\n");
		if (line[i][0] == '\'' || line[i][0] == '\"')
			line[i] = ft_substr(line[i], 1, ft_strlen(line[i]) - 2);
		while (line[i][j] != '\0')
		{
			if (line[i][j] == '\'' || line[i][j] == '\"')
				remove_middle_quotes(line, j);
			j++;
		}
		j = 0;
		i++;
	}
	if (*line)
	{
		line++;
		remove_token_quotes(line);
	}
//	printf("mais embaixo na remove_token_quotes\n");
	return (line);
}


// echo "'jorge' ale"
// look_for_quotes: "'jorge' ale"\0
// remove_quotes: 'jorge' ale\0