/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:34:34 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/20 18:04:14 by joeduard         ###   ########.fr       */
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

char *handle_quotes(char *str)
{
    char *no_quotes;
    char *from_single_quotes;
    char *from_double_quotes;
    int quote_pos;
    int i;
    int j;

    i = 0;
    j = 0;

    if (str)
    {
        from_single_quotes = ft_strchr(str, SQUOTES);
        from_double_quotes = ft_strchr(str, DQUOTES);
        if (from_single_quotes)
            no_quotes = ft_strtrim(from_single_quotes, "\'");
        else if (from_double_quotes)
            no_quotes = ft_strtrim(from_double_quotes, "\"");
        quote_pos = find_quote(str);
        while (str[i])
        {
            if (str[i] == SQUOTES || str[i] == DQUOTES)
            {
                while (no_quotes[j])
                    str[quote_pos++] = no_quotes[j++];
                str[quote_pos] = '\0';
                break;
            }
            i++;
        }
        printf("str: %s\n", str);
    }
    return (str);
}
