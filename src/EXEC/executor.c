/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/19 21:38:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_execve(t_data *data, int argve_index)
{
	char *path_aux;
	int i;

	path_aux = NULL;
	i = 0;  
	while (data->command_path[i])
    {
    	path_aux = ft_strjoin(data->command_path[i], data->argve[argve_index][0]);
    	if (execve(path_aux, data->argve[argve_index], data->envp) < 0)
		{
			if (path_aux)
			{
				free(path_aux);
				path_aux = NULL;
			}								
    		i++;
		}
    }
	printf("Minishell: command not found: %s\n", data->argve[argve_index][0]); 
	if (path_aux)
		free(path_aux);
}

void builtin_exec(t_data *data, int code)
{
	if (code == EXIT)		
		mini_exit(data);				
	else if (code == CD)
		chdir(data->argve[0][1]);
	else if (code == ECHO)
		echo(data);
	else if (code == HELLO)
		hello();	
	else if (code == HELP)
		open_help();	
}

int execute_pid(t_data *data, int id) 
{
	int builtin_flag;

	exec_signals();
	redirect_filter(data, id);
	builtin_flag = is_builtins(data->argve[id][0]);	
	if (builtin_flag)
	{
		builtin_exec(data, builtin_flag);
		exit (SUCCESS);
	}
	else
	{
		ft_execve(data, id);
		exit (FAILURE); 
	}
}

int executor(t_data *data) //executor
{
	int id;
	int fd[data->number_of_pipes][2];
	int pid[data->number_of_pipes + 1];
		
	check_exit(data);	
	open_pipes(data->number_of_pipes, fd);
	id = 0;
	while (id < data->number_of_pipes + 1)
	{
		pid[id] = fork();
		if (pid[id] < 0)
		{
			perror("fork");
			return FAILURE;
		}
		if (pid[id] == 0)
		{	
			scope_fd_select(id, data->number_of_pipes, fd); 			
			execute_pid(data, id);
			return SUCCESS;
		}
		id++;
	}
	main_process_handler(pid, data->number_of_pipes, fd);
	return SUCCESS;//tratar erros
}
