/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/26 14:35:53 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		find_vars(char **argve)
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

void	make_space(char **argve, int start)
{
	int	i;

	i = 0;
	while (argve[i])
		i++;
	argve[i + 1] = NULL;
	while (i > start)
	{
		if (argve[i])
			free(argve[i]);
		argve[i] = ft_strdup(argve[i - 1]);
		i--;
	}
	free(argve[i]);
}

int		arglist_size(char **arglist)
{
	int	i;

	i = 0;
	while (arglist[i])
		i++;
	return (i);
}

void	move_argve(char **temp, char **argve)
{
	while (*argve)
	{
		*temp = *argve;
		argve++;
		temp++;
	}
}

void	expander(t_data *data)
{
	int		i;
	int		cmdstr_size;
	int		argve_size;
	char	*value;
	char	**cmdstr;
	char	**temp_argve;

	i = 0;
	while (find_vars(data->argve[0]) != -1)
	{
		data->exec_flag = 1;
		i = find_vars(data->argve[0]);
		value = find_in_list(data->argve[0][i], data->vars);
		if (ft_strchr(value, ' '))
		{
			cmdstr = ft_split(value, ' ');
			cmdstr_size = arglist_size(cmdstr);
			argve_size = arglist_size(data->argve[0]);
			temp_argve = (char **)malloc((cmdstr_size + argve_size + 1) * sizeof(char *));
			ft_memcpy(temp_argve, data->argve[0], argve_size * sizeof(char *));
			free(data->argve[0]);
			data->argve[0] = temp_argve;
			data->argve[0][argve_size] = 0x0;
			data->argve[0][i] = ft_strdup(*cmdstr);
			cmdstr++;
			i++;
			while (*cmdstr)
			{
				make_space(data->argve[0], i);
				data->argve[0][i] = ft_strdup(*cmdstr);
				cmdstr++;
				i++;
			}
		}
		else
		{
			free(data->argve[0][i]);
			data->argve[0][i] = ft_strdup(value);
		}
	}
}