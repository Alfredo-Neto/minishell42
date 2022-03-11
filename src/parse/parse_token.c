/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/11 13:38:28 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// function for parsing command words
void	parse_space(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break ;
		if (strlen(parsed[i]) == 0)
			i--;
		i++;
	}
}

int	process_string(char *str, char **parsed, char **parsedpipe)
{
	char	*strpiped[2];
	int		piped;

	piped = 0;
	piped = parse_pipe(str, strpiped);
	if (piped)
	{
		parse_space(strpiped[0], parsed);
		parse_space(strpiped[1], parsedpipe);
	}
	else
		parse_space(str, parsed);
	if (own_cmd_handler(&str))
	{
		printf("IF\n");
		return (0);
	}
	else
	{
		printf("ELSE");
		return (1 + piped);
	}
}
