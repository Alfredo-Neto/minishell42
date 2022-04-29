/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:05:19 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/27 20:05:34 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_std_fds(int *fd)
{
	dup2(fd[STDOUT], STDOUT_FILENO);
	close(fd[STDOUT]);
	dup2(fd[STDIN], STDIN_FILENO);
	close(fd[STDIN]);
}

void	save_std_fds(int *fd)
{
	fd[STDIN] = dup(STDIN_FILENO);
	fd[STDOUT] = dup(STDOUT_FILENO);
}
