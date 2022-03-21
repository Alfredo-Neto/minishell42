/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/21 19:43:48 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


//void 

//multiple_exec(data);
//single_exec(data);

/*
// Function where the system command is executed
void exec_args(char **parsed)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		return;
	}
}

// Function where the piped system commands is executed
void exec_args_piped(char **parsed, char **parsedpipe)
{
	int pipefd[2];
	pid_t p1;
	pid_t p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
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
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		p2 = fork();
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
			if (execvp(parsedpipe[0], parsedpipe) < 0)
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

*/

// Function to execute builtin commands


void switch_builtin(t_data *data, int code)
{
	if (code == EXIT)
	{
		printf("\nGoodbye!\n");
		exit_minishell(data, SUCCESS);
	}
	else if (code == CD)
		chdir(data->argve[0][1]);
	else if (code == ECHO)
		echo(data);
	else if (HELLO == 4) //retirar!
	{
		int username;
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is not a place to play around."
			   "\nUse help to know more..\n",
			   username);		
	}
}

void executor(t_data *data)
{
	//
	
}

