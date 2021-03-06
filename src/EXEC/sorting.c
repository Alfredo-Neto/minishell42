/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:16:34 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/02 22:33:41 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtins(char *cmd)
{
	int		i;
	int		switcher;
	char	*builtin_cmd[NUMBER_OF_BUILTINS];

	i = -1;
	switcher = 0;
	builtin_cmd[0] = "exit";
	builtin_cmd[1] = "cd";
	builtin_cmd[2] = "echo";
	builtin_cmd[3] = "hello";
	builtin_cmd[4] = "help";
	builtin_cmd[5] = "pwd";
	builtin_cmd[6] = "env";
	builtin_cmd[7] = "export";
	builtin_cmd[8] = "unset";
	while (++i < NUMBER_OF_BUILTINS)
	{
		if (ft_strcmp(cmd, builtin_cmd[i]) == 0)
		{
			switcher = i + 1;
			break ;
		}
	}
	return (switcher);
}
