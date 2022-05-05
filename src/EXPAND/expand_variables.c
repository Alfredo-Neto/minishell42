/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/05 20:26:33 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
char	**new_argve(char *value, t_data *data)
{
	char	**cmdstr;
	char	**temp_argve;
	int		cmdstr_size;
	int		argve_size;

	cmdstr = ft_split(value, ' ');
	cmdstr_size = ft_str_count(cmdstr);
	argve_size = ft_str_count(data->argve[0]);
	temp_argve = (char **)malloc((cmdstr_size + argve_size + 1) * \
		sizeof(char *));
	ft_memcpy(temp_argve, data->argve[0], argve_size * sizeof(char *));
	free(data->argve[0]);
	data->argve[0] = temp_argve;
	data->argve[0][argve_size] = 0x0;
	return (cmdstr);
}

// makes room for new args and inserts it into data structure
void	insert_new_args(t_data *data, char **cmdstr, int i)
{
	free(data->argve[0][i]);
	data->argve[0][i] = ft_strdup(*cmdstr);
	while (*(++cmdstr))
	{
		make_space(data->argve[0], ++i);
		data->argve[0][i] = ft_strdup(*cmdstr);
	}
}

void	expander(t_data *data)
{
	int		i;
	int		id;
	char	**cmdstr;
	t_vdt	vdt;

	id = 0;
	while (data->argve[0])
	{
		while (find_vars(data->argve[0]) != -1)
		{
			i = find_vars(data->argve[0]);
			vdt = find_in_list(data->argve[0][i], data->vars);
			if (!vdt.value)
			{
				free(data->argve[0][i]);
				move_ptrs_back(&data->argve[0][i]);
				continue ;
			}
			cmdstr = new_argve(vdt.value, data);
			data->exec_flag = 1;
			if (ft_strchr(vdt.value, ' '))
				insert_new_args(data, cmdstr, i);
			else
			{
				free(data->argve[0][i]);
				data->argve[0][i] = ft_strdup(vdt.value);
			}
			if (vdt.is_question_mark)
				free(vdt.value);
			double_free((void ***)&cmdstr);
		}
		i = 0;
		while (data->argve[0][i])
			unmask_character(data->argve[0][i++], 7, '$');
		id++;
		data->argve++;
	}
	data->argve -= id;
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
