/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/07 00:30:54 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int main_process_handler(int *pid, int n_pipes, int fd[n_pipes][2])
{
	int count;
	
	count = 0;
	while (count < n_pipes)
	{
		close(fd[count][0]);
		close(fd[count][1]);
		count++;
	}
	count = 0;
	while (count < n_pipes + 1)
	{
		waitpid(pid[count], NULL, 0);
		count++;
	}
	return SUCCESS;//tratar erros	
}