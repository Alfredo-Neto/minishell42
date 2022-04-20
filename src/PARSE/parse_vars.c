/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:10 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/04/20 13:09:53 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// gets and returns the name of the variable
char	*get_var_name(char *input)
{
	int		i;
	char	*name;

	i = 0;
	while (input[i] != '=')
		i++;
	name = (char *)malloc(i * sizeof(char) + 1);
	ft_strlcpy(name, input, i + 1);
	return (name);
}

// gets and returns the value of the variable
char	*get_var_value(char *input, int parse)
{
	int		i;
	char	*value;

	i = 0;
	while (*input != '=')
		input++;
	input++;
	if (*input == '\"')
	{
		input++;
		while (input[i] != '\"' && input[i])
			i++;
	}
	else
		if (parse)
			while (input[i] != ' ' && input[i])
				i++;
		else
			while (input[i])
				i++;
	value = (char *)malloc(i * sizeof(char) + 1);
	ft_strlcpy(value, input, i + 1);
	return (value);
}

// checks for variables in the input string and stores them on a linked list
void	grab_vars(t_data *data, char *str, int parse)
{
	char *name;
	char *value;

	if (ft_strchr(str, '='))
	{
		data->exec_flag = -1;
		if (parse)
		{
			while (*str != '=')
				str++;
			while (*str != ' ' && str != data->input)
				str--;
			if (*str == ' ') 
				str++;
		}
		name = get_var_name(str);
		value = get_var_value(str, parse);
		if (!data->vars)
			data->vars = new_node(name, value);
		else
		{
			str = find_in_list(name, data->vars);
			if (*str == '$')
				add_to_list(&data->vars, name, value);
			else
				change_in_list(data->vars, name, value);
		}
		free(name);
		free(value);
	}
}
