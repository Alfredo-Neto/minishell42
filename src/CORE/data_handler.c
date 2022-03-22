/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 23:22:32 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{	
	data->input = NULL;
	data->argve = NULL; //(cmd + args)
	data->envp = NULL;
	data->no_pipes = -1;
	data->exec_flag = -1;
}

void	data_clean(t_data *data)
{
	free_str(&data->input);
	free_triple_str(&data->argve);
	data->no_pipes = -1;
	data->exec_flag = -1;
}


