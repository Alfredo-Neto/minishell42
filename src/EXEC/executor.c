/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/07 00:30:54 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void executor(t_data *data)
{
	exec_selector(data);  
	if (data->exec_mode == WITH_PIPE)
		multiple_exec(data);
	else if (data->exec_mode == NO_PIPE)
		single_exec(data);
}

void ft_execve(t_data *data, int argve_index)
{
	char *path_aux;
	int i;

	path_aux = NULL;
	i = 0;  
	while (data->command_path[i])
    {
    	path_aux = ft_strjoin(data->command_path[i], data->argve[argve_index][0]);
    	if (execve(path_aux, data->argve[argve_index], data->envp) < 0 )
		{
			if (path_aux)
			{
				free(path_aux);
				path_aux = NULL;
			}								
    		i++;
		}
    }
	printf("%s: command not found\n", data->argve[argve_index][0]); //implementar c saida wait, no pai
	if (path_aux)
		free(path_aux);
}

int fork_and_execute(t_data *data, int argve_index, int builtin_flag) //[ok]
{
	pid_t	chlpid;
	int		wstatus;	
	
	chlpid = fork();
	if (chlpid < 0)
	{
		perror("Fork failed"); 
		return (FAILURE);
	}
	if (chlpid == 0) 
	{	
		if (builtin_flag)
		{
			builtin_exec(data, builtin_flag);
			return (SUCCESS);
		}
		else
		{
			ft_execve(data, argve_index);
			//printf("\nCould not execute command..\n");
			return (FAILURE); //			
		}		
	}
	else
	{
		waitpid(chlpid, &wstatus, 0); //wait(&wstatus);	
		return (SUCCESS);
	}		
}

/*
* Só fiz a SINGLE EXEC. Parei para resolver o problema do exit: Saí depois de umas vezes, apenas
*
*
*/

void single_exec(t_data *data) // [ok]
{
	int	  builtin_flag;
	int index;                 

	index = 0;

	builtin_flag = is_builtins(data->argve[index][0]);
	if (builtin_flag == EXIT) //Exit n forka, sai direto
		mini_exit(data);
	else
		fork_and_execute(data, index, builtin_flag);
}


//FALTA IMPLEMENTAR!::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void multiple_exec(t_data *data)
{
	int pipefd[2];
	int index;
	int	  builtin_flag;
	pid_t p1;
	pid_t p2;

	index = 0;
	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized\n");
		return;
	}
	p1 = fork();
	builtin_flag = is_builtins(data->argve[index][0]);
	if (p1 < 0)
	{
		printf("\nCould not fork\n");
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
			printf("\nCould not execute command 1..\n");
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
			printf("\nCould not fork\n");
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
				printf("\nCould not execute command 2..\n");
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


// Function to call builtin commands [ok]
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




