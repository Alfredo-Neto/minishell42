/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path_tester.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lang <lang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:06 by lang              #+#    #+#             */
/*   Updated: 2022/05/04 13:16:44 by lang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int absolute_path_tester(char *cmd)
{
	if (!cmd)
		return (FALSE);
	else
	{
		while(*cmd)
		{
			if (*cmd == '/')
				return (TRUE);
			cmd++;
		}
	}
	return (FALSE);
}
