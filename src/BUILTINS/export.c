/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:32:15 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/04/28 00:12:51 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// alloc a bigger envp
// point older variables to new envp

void	relocate_envp(char **old_envp, char **new_envp, char *new_var)
{
	while (*old_envp)
	{
		*new_envp = *old_envp;
		old_envp++;
		new_envp++;
	}
	*new_envp = ft_strdup(new_var);
	new_envp++;
	*new_envp = NULL;
}

void	export(t_data *data, int id)
{
	char	*name;
	char	*value;
	char	**new_envp;
	t_vdt	vdt;
	int		envp_size;
	int		i;

	i = 1;
	envp_size = ft_str_count(data->envp) + ft_str_count(data->argve[id]);
	new_envp = (char**)malloc(sizeof(char**) * (envp_size + 2));
	relocate_envp(data->envp, new_envp, data->argve[id][i]);
	while (data->argve[id][i])
	{
		name = get_var_name(data->argve[id][i]);
		value = get_var_value(data->argve[id][i]);
		vdt = find_in_list(name, data->vars);
		if (ft_strcmp(vdt.value, "$") == 0)
		{
			free(value);
			free(name);
			break;
		}
		
		free(value);
		free(name);
		i++;
	}
}