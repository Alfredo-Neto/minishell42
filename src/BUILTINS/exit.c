/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/10 10:41:58 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_minishell(t_data *data, int status)
{	
	data_clean(data);
	if (data->old_input)
		free(data->old_input);
	double_free((void ***)&data->command_path);
	double_free((void ***)&data->envp);
	clear_list(data->vars);
	rl_clear_history();
	free(data);
	exit(g_status_code | status);
}

void	mini_exit(t_data *data)
{
	int		args;

	args = ft_str_count(data->argve[0]);
	if (args > 2)
		ft_printf(STDERR, "Minishell: exit: too many arguments\n");
	else
	{
		printf("Goodbye!\n");
		if (args == 1)
			exit_minishell(data, 0);
		else if (args == 2)
			exit_minishell(data, ft_atoi(data->argve[0][1]));
	}
}
