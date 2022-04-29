/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:41:36 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/29 17:11:08 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*reverse_quotes_treat(char *str)
{
	int	i;

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
