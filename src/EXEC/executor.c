/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/22 21:57:49 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void executor(t_data *data)
{
	exec_selector(data);
}

// Function to call one sys cmds
void single_exec(t_data *data) //char **parsed)
{
	pid_t pid;
	int	  builtin_flag;
	int index;

	index = 0;

	builtin_flag = is_builtins(data->argve[index][0]);

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0)
	{
		if (builtin_flag)
			builtin_exec(data, builtin_flag);
		else if (execvp(data->argve[index][0], data->argve[0]) < 0)//mudar p execve - n vai rodar
			printf("\nCould not execute command..");
		exit(0);
	}
	else
	{
		wait(NULL);
		return;
	}
}

// Function to call multiple sys cmds
void multiple_exec(t_data *data) //char **parsed, char **parsedpipe)
{
	int pipefd[2];
	int index;
	int	  builtin_flag;
	pid_t p1;
	pid_t p2;

	index = 0;
	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	builtin_flag = is_builtins(data->argve[index][0]);
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return;
	}
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (builtin_flag)
			builtin_exec(data, builtin_flag);
		else if (execvp(data->argve[index][0], data->argve[0]) < 0) //n vai rodar
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		index++;
		p2 = fork();
		builtin_flag = is_builtins(data->argve[index][0]);
		if (p2 < 0)
		{
			printf("\nCould not fork");
			return;
		}
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (builtin_flag)
				builtin_exec(data, builtin_flag);
			else if (execvp(data->argve[index][0], data->argve[1]) < 0) //n vai rodar
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}


// Function to call builtin commands
void builtin_exec(t_data *data, int code)
{
	if (code == EXIT)		
		exit_minishell(data, code);
	else if (code == CD)
		chdir(data->argve[0][1]);
	else if (code == ECHO)
		echo(data);
	else if (code == HELLO)
		hello();	
	else if (code == HELP)
		open_help();	
}



