/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path_tester.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:06 by lang              #+#    #+#             */
/*   Updated: 2022/05/10 10:43:32 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int absolute_path_tester(char *cmd)
{
	if (!cmd)
		return (FALSE);
	while (*cmd)
	{
		if (*cmd == '/')
			return (TRUE);
		cmd++;
	}
	return (FALSE);
}
