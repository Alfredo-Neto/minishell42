/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/28 13:15:17 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// functions for parsing command line
void	parser(t_data *data)
{
	int	i;

	i = 0;
	while (data->argve[0][i])
		grab_vars(data, data->argve[0][i++]);
	if (is_builtins(data->argve[0][0]) == EXPORT)
		data->exec_flag = 1;
	//parse_quotes();
	//parse_redirects();
}
