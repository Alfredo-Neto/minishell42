/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/12 23:37:24 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_vars(t_data *data, int id);

void	expander(t_data *data)
{
	int		i;
	int		id;

	id = 0;
	while (data->argve[id])
	{
		i = 0;
		search_vars(data, id);
		while (data->argve[id][i])
			unmask_character(data->argve[id][i++], 7, '$');
		id++;
	}
}

static void	search_vars(t_data *data, int id)
{
	char	**cmdstr;
	t_vdt	vdt;
	int		i;

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
}
