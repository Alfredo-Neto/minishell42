/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:26:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/01 13:38:02 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect(char *file, int flags, int std_fd)
{
	int	fd;

	if (!std_fd)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0777);
	if (fd == -1)
		perror("Minishell: Open function failed:");
	else
	{
		dup2(fd, std_fd);
		close(fd);
	}
}

int	redirect_filter(t_data *data, int id)
{
	int	i;

	if (!data->file[id])
		return (SUCCESS);
	i = 0;
	while (data->file_mode[id][i])
	{
		if (data->file_mode[id][i] == GREAT)
			redirect(data->file[id][i], O_WRONLY | O_CREAT | O_TRUNC, STDOUT);
		else if (data->file_mode[id][i] == GREATGREAT)
			redirect(data->file[id][i], O_WRONLY | O_CREAT | O_APPEND, STDOUT);
		else if (data->file_mode[id][i] == LESS)
			redirect(data->file[id][i], O_RDONLY | O_CREAT, STDIN);
		else if (data->file_mode[id][i] == LESSLESS)
			if (heredoc(data->file[id][i]))
				return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
