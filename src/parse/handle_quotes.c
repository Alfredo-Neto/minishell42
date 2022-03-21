/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:34:34 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/21 17:52:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int find_quote(char *str)
{
    int i;

    i = 0;
    if (str == 0)
        return (EXIT_FAILURE);
    while (str[i] != '\0')
    {
        if (str[i] == '\"' || str[i] == '\'')
            return (i);
        i++;
    }
    return (NO_QUOTES_FOUND);
}

void	single_quotes(char *from_single_quotes, char *str)
{
    char *no_quotes;
   	int quote_pos;
   	int i;
	int j;
	
	i = 0;
	j = 0;
	no_quotes = ft_strtrim(from_single_quotes, "\'");
	
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
        if (from_single_quotes)
			single_quotes(from_single_quotes, str);
        else if (from_double_quotes)
			double_quotes(from_double_quotes, str);
        printf("str: %s\n", str);
    }
    return (str);
}
