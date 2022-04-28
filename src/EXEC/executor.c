/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/28 00:00:14 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execve(t_data *data, int id)
{
	int		i;

	data->path_aux = NULL;
	i = 0;
	while (data->command_path[i])
	{
		data->path_aux = ft_strjoin(data->command_path[i], \
			data->argve[id][0]);
		if (execve(data->path_aux, data->argve[id], data->envp) < 0)
		{
			if (data->path_aux)
			{
				free(data->path_aux);
				data->path_aux = NULL;
			}
			i++;
		}
	}
	ft_printf(STDERR, "Minishell: command not found: %s\n", data->argve[id][0]);
	exit(FAILURE);
}

void	builtin_exec(t_data *data, int code, int id)
{
	if (code == EXIT)
		mini_exit(data);
	else if (code == CD)
		cd(data, id);
	else if (code == ECHO)
		echo(data);
	else if (code == HELLO)
		hello();
	else if (code == HELP)
		open_help();
	else if (code == PWD)
		pwd();
	else if (code == ENV)
	 	env(data);
	else if (code == EXPORT)
		export(data, id);
	else if (code == UNSET)
		unset(data, id);
}

int	execute_pid(t_data *data, int id)
{
	int	builtin_flag;

	exec_signals();
	builtin_flag = is_builtins(data->argve[id][0]);
	if (builtin_flag)
		builtin_exec(data, builtin_flag, id);
	else
	{
		data->pid[id] = fork();
		if (data->pid[id] < 0)
		{
			perror("Minishell: Could not fork proccess: ");
			return (FAILURE);
		}
		if (!data->pid[id])
			ft_execve(data, id);
	}
	return (SUCCESS);
}

void	create_executor_parametes(t_data *data)
{
	int		i;

	i = 0;
	data->pid = (int *)ft_calloc(sizeof(int), data->number_of_pipes + 1);
	data->fd = (int **)ft_calloc(sizeof(int *), data->number_of_pipes + 1);
	if (!data->pid || !data->fd)
		exit_minishell(data, FAILURE);
	while (i < data->number_of_pipes + 1)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->fd[i])
			exit_minishell(data, FAILURE);
		i++;
	}
}

int	executor(t_data *data)
{
	int		id;
	int		save_fd[2];

	id = 0;
	check_exit(data);
	create_executor_parametes(data);
	open_pipes(data);
	if (data->exec_flag == -1)
		return (SUCCESS);
	while (id < data->number_of_pipes + 1)
	{
		save_std_fds(save_fd);
		close_other_fds(id, data);
		file_descriptor_handler(id, data);
		if (redirect_filter(data, id, save_fd))
			break ;
		if (execute_pid(data, id++))
			break ;
		restore_std_fds(save_fd);
	}
	main_process_handler(data);
	return (SUCCESS); //tratar erros
}
