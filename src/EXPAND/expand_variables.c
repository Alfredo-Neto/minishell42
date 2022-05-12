/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/12 00:49:26 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_ptrs_back(char **argve);

// finds the variables on argve
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

// creates space on the argve for the expanded variables
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

// allocates a bigger argve, copies the old to the new one and frees the old one
char	**new_argve(char *value, t_data *data, int id)
{
	char	**cmdstr;
	char	**temp_argve;
	int		cmdstr_size;
	int		argve_size;

	cmdstr = ft_split(value, ' ');
	cmdstr_size = ft_str_count(cmdstr);
	argve_size = ft_str_count(data->argve[id]);
	temp_argve = (char **)malloc((cmdstr_size + argve_size + 1) * \
		sizeof(char *));
	ft_memcpy(temp_argve, data->argve[id], argve_size * sizeof(char *));
	free(data->argve[id]);
	data->argve[id] = temp_argve;
	data->argve[id][argve_size] = 0x0;
	return (cmdstr);
}

// makes room for new args and inserts it into data structure
void	insert_new_args(t_data *data, char **cmdstr, int i, int id)
{
	free(data->argve[id][i]);
	data->argve[id][i] = ft_strdup(*cmdstr);
	while (*(++cmdstr))
	{
		make_space(data->argve[id], ++i);
		data->argve[id][i] = ft_strdup(*cmdstr);
	}
}

void	expander(t_data *data)
{
	int		i;
	int		id;
	char	**cmdstr;
	t_vdt	vdt;

	id = 0;
	while (data->argve[id])
	{
		while (find_vars(data->argve[id]) != -1)
		{
			i = find_vars(data->argve[id]);
			vdt = find_in_list(data->argve[id][i], data->vars);
			if (!vdt.value)
			{
				free(data->argve[id][i]);
				move_ptrs_back(&data->argve[id][i]);
				continue ;
			}
			cmdstr = new_argve(vdt.value, data, id);
			data->exec_flag[id] = 1;
			if (ft_strchr(vdt.value, ' '))
				insert_new_args(data, cmdstr, i, id);
			else
			{
				free(data->argve[id][i]);
				data->argve[id][i] = ft_strdup(vdt.value);
			}
			if (vdt.is_question_mark)
				free(vdt.value);
			double_free((void ***)&cmdstr);
		}
		i = 0;
		while (data->argve[id][i])
			unmask_character(data->argve[id][i++], 7, '$');
		id++;
	}
}

void	move_ptrs_back(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
}
