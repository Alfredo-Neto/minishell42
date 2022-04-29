/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:03:00 by azamario          #+#    #+#             */
/*   Updated: 2022/04/29 16:10:06 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	return (SUCCESS);
}
