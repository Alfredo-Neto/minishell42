/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/13 17:47:52 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{	
	int	i;

	i = 0;
	data->input = NULL;
	data->argve = NULL; //(cmd + args)
	data->vars = NULL;
	data->number_of_pipes = -1;
	data->exec_flag = -1;
	while (data->envp[i])
		grab_vars(data, data->envp[i++], FALSE);
}

void	data_clean(t_data *data)
{
	free_str(&data->input);
	free_triple_str(&data->argve);
	data->number_of_pipes = -1;
	data->exec_flag = -1;
}


