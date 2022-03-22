/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:27:43 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 13:36:53 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_minishell(t_data *data, int status)
{
	if (status == 0)
		printf("\nGoodbye!\n");
	data_clean(data);
	free_double_str(data->envp);
	rl_clear_history();
	exit (status);
}