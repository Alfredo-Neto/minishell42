/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:34:28 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/15 23:35:12 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_vars(t_data *data, int id, int i, char *var_value);
static char	*pull_var_value(char *s[0], t_vars *vars);
static char	*ret_full_value(char *s, int offset, char *value, int i);

void	expander(t_data *data)
{
	int		i;
	int		id;
	char	*var_value;

	id = -1;
	while (data->argve[++id])
	{
		while (find_vars(data->argve[id]) != -1)
		{
			i = find_vars(data->argve[id]);
			var_value = pull_var_value(data->argve[id] + i, data->vars);
			if (!var_value || !*var_value)
			{
				if (!*var_value)
					ft_super_free((void **)&var_value);
				free(data->argve[id][i]);
				move_ptrs_back(&data->argve[id][i]);
				continue ;
			}
			save_vars(data, id, i, var_value);
		}
		i = 0;
		while (data->argve[id][i])
			unmask_character(data->argve[id][i++], 7, '$');
	}
}

static void	save_vars(t_data *data, int id, int i, char *var_value)
{
	char	**cmdstr;

	cmdstr = new_argve(var_value, data, id);
	if (ft_strchr(var_value, ' '))
		insert_new_args(data, cmdstr, i, id);
	else
	{
		free(data->argve[id][i]);
		data->argve[id][i] = ft_strdup(var_value);
	}
	double_free((void ***)&cmdstr);
	ft_super_free((void **)&var_value);
}

static char	*pull_var_value(char **s, t_vars *vars)
{
	char	*var_name;
	char	*full_value;
	int		offset;
	int		i;
	t_vdt	vdt;

	offset = 0;
	while (s[0][offset] != '$')
		offset++;
	i = offset + 1;
	while (ft_isalpha(s[0][i]) || ft_isdigit(s[0][i]) || s[0][i] == '_')
			i++;
	if (s[0][i] == '?')
		i++;
	var_name = ft_substr(s[0], offset, i - offset);
	vdt = find_in_list(var_name, vars);
	free(var_name);
	if (!vdt.value)
	{
		ft_strcut(s, offset, i);
		return (ft_strdup(*s));
	}
	full_value = ret_full_value(*s, offset, vdt.value, i);
	if (vdt.is_allocated)
		free(vdt.value);
	return (full_value);
}

static char	*ret_full_value(char *s, int offset, char *value, int i)
{
	char	*ret;
	char	*prefix;

	prefix = ft_substr(s, 0, offset);
	ret = ft_mult_join(3, prefix, value, s + i);
	free(prefix);
	return (ret);
}
