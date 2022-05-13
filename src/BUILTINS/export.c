/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:32:15 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/05/12 23:39:05 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sorts envp content and prints on screen
void	sort_export(char **envp)
{
	char	**temp_envp;
	int		i;
	int		last;

	temp_envp = envp;
	temp_envp = new_bigger_envp(envp);
	i = relocate_envp(envp, temp_envp, "----temp----");
	last = i--;
	free(temp_envp[last]);
	while (i > 0)
	{
		if (ft_strcmp(temp_envp[i], temp_envp[i - 1]) < 0)
		{
			temp_envp[last] = temp_envp[i];
			temp_envp[i] = temp_envp[i - 1];
			temp_envp[i - 1] = temp_envp[last];
			i = last;
		}
		i--;
	}
	while (i < last)
		printf("declare -x %s\n", temp_envp[i++]);
	free(temp_envp);
}

// checks if expression is "export $", an invalid input
int	invalid_var(char ***argve, int id)
{
	if (ft_strcmp(argve[id][0], "export") == 0 &&
		ft_strcmp(argve[id][1], "$") == 0 &&
		argve[id][2] == 0x0)
		return (TRUE);
	else
		return (FALSE);
}

void	export(t_data *data, int id)
{
	int		i;

	i = 0;
	while (data->argve[id][i])
	{
		if (is_builtins(data->argve[id][i]) == 0)
		{
			if (invalid_var(data->argve, id))
				printf("bash: export: `$': not a valid identifier\n");
			else if (ft_strchr(data->argve[id][i], '='))
				upd_envp_w_def(data, i, id);
			else
				upd_envp_no_def(data, i, id);
		}
		else if (!(data->argve[id][i + 1]))
			sort_export(data->envp);
		i++;
	}
}
