/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:34:34 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/22 14:04:39 by joeduard         ###   ########.fr       */
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
	no_quotes = ft_strtrim(from_single_quotes, "\'");
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
        if(from_single_quotes && from_double_quotes)
            mix_quotes(from_single_quotes, from_single_quotes, str);
        else if (from_single_quotes)
            single_quotes(from_single_quotes, str);
        else if (from_double_quotes)
			double_quotes(from_double_quotes, str);
        printf("str: %s\n", str);
    }
    return (str);
}
