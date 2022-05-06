/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/05/05 23:06:57 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static int	find_path_and_execve(t_data *data, int id)
{
	int		i;
	char	*path_aux;

	path_aux = NULL;
	g_status_code = 0;
	i = 0;
	path_aux = NULL;
	while (data->command_path[i])
	{
		path_aux = ft_strjoin(data->command_path[i], data->argve[id][0]);
		if (execve(path_aux, data->argve[id], data->envp) < 0)
		{
			if (path_aux)
			{
				free(path_aux);
				path_aux = NULL;
			}
			i++;
		}
	}
	return (FAILURE);
}

void	ft_execve(t_data *data, int id)
{
	if (absolute_path_tester(data->argve[id][0]))
		execve(data->argve[id][0], data->argve[id], data->envp);
	else if (data->command_path)
		find_path_and_execve(data, id);
	ft_printf(STDERR, "Minishell: %s: No such file or directory\n", data->argve[id][0]);
	g_status_code = 127;
	exit(127);
}

void	builtin_exec(t_data *data, int code, int id)
{
	if (code == EXIT && !data->number_of_pipes)
		mini_exit(data);
	else if (code == CD && !data->number_of_pipes)
		cd(data, id);
	else if (code == ECHO)
		echo(data, id);
	else if (code == HELLO)
		hello();
	else if (code == HELP)
		open_help();
	else if (code == PWD)
		pwd();
	else if (code == ENV)
		env(data);
	else if (code == UNSET && !data->number_of_pipes)
		unset(data, id);
	else if (code == EXPORT && !data->number_of_pipes)
		export(data, id);
}

int	execute_pid(t_data *data, int id)
{
	int	builtin_flag;

	close_other_fds(id, data);
	file_descriptor_handler(id, data);
	if (!redirect_filter(data, id))
	{
		exec_signals();
		builtin_flag = is_builtins(data->argve[id][0]);
		if (builtin_flag)
			builtin_exec(data, builtin_flag, id);
		else
			ft_execve(data, id);
	}
	exit(SUCCESS);
}

void	create_executor_parametes(t_data *data)
{
	int		i;

	i = 0;
	data->pid = (int *)ft_calloc(sizeof(int), data->number_of_pipes + 1);
	data->fd = (int **)ft_calloc(sizeof(int *), data->number_of_pipes + 1);
	if (!data->pid || !data->fd)
		exit_minishell(data, FAILURE);
	while (i < data->number_of_pipes)
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

	if (data->exec_flag == -1)  // added to avoid execution if input is var definition
		return (SUCCESS);
	signal(SIGINT, handler);
	if (!data->number_of_pipes && is_builtins(data->argve[0][0]))
		return (execute_one_cmd(data));
	id = -1;
	create_executor_parametes(data);
	open_pipes(data);
	while (++id < data->number_of_pipes + 1)
	{
		data->pid[id] = fork();
		if (data->pid[id] < 0)
		{
			perror("Minishell: Could not fork proccess: ");
			return (FAILURE);
		}
		if (!data->pid[id])
			execute_pid(data, id);
	}
	main_process_handler(data);
	return (SUCCESS);
}
