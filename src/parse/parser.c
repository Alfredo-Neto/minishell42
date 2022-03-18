/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/18 17:23:33 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function for finding pipe
int parse_pipe(char *str, char **strpiped)
{
	strpiped = ft_split(str, '|');
	if (strpiped[1] == NULL)
		return (0);
	else
		return (1);
}

// function for parsing command words
char **parse_space(char *str, char **parsed)
{
	int i;

	i = 0;

	parsed = ft_split(str, ' ');

	// print variable
	while (parsed[i])
	{
		printf("......................PARSED: %s\n", parsed[i]);
		i++;
	}

	return (parsed);
}

int process_string(char *str, char **parsed, char **parsedpipe)
{
	char *strpiped[2];
	int piped;

	piped = 0;
	piped = parse_pipe(str, strpiped);
	if (piped)
	{
		parsed = parse_space(strpiped[0], parsed);
		parsed = parse_space(strpiped[1], parsedpipe);
	}
	else
		parsed = parse_space(str, parsed);
	if (handle_builtins(parsed))
	{
		printf("                                      BUILTIN (yes)\n");
		return (SUCCESS);
	}
	else
	{
		printf("                                      BUILTIN (no)");
		return (1 + piped);
	}
}
