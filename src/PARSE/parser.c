/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/23 11:58:56 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// functions for parsing command line
void	parser(t_data *data)
{
	grab_vars(data);
	//parse_quotes();
	//parse_redirects();
}
