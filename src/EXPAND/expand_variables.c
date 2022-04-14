/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/14 20:55:45 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_vars(char **argve)
{
	int	i;

	i = 0;
	while (argve[i])
	{
		if (ft_strchr(argve[i], '$'))
			return (i);
		i++;
	}
	return (-1);
}

void expander(t_data *data)
{
	int	i;
	char *value;

	i = 0;
	if (ft_strchr(data->string, '$'))
	{
		data->exec_flag = 1;
		i = find_vars(data->argve[0]);
		value = find_in_list(data->argve[0][i], data->vars);
		free(data->argve[0][i]);
		data->argve[0][i] = ft_strdup(value);
	}
	else
		printf("there is no variable\n");
}