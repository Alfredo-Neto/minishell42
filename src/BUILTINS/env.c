/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:03:00 by azamario          #+#    #+#             */
/*   Updated: 2022/04/25 02:30:02 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_data *data)
{
	int i;

	i = 0;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	return (SUCCESS);
}
