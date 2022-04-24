/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/24 14:04:18 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// functions for parsing command line
void	parser(t_data *data)
{
	grab_vars(data, data->input, TRUE);
	//parse_quotes();
	//parse_redirects();
}
