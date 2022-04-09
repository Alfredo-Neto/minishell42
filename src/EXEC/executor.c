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

//triagem de execução -> com ou sem pipe
void executor(t_data *data)
{
	exec_selector(data);  
	//if (data->exec_mode == WITH_PIPE)
		multiple_exec(data);
	//else if (data->exec_mode == NO_PIPE)
	//	single_exec(data);
}

//executa o comando argve_index
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
	printf("Minishell: command not found: %s\n", data->argve[argve_index][0]); 
	if (path_aux)
		free(path_aux);
}

//Cria um filho e executa Builtin ou Sys_cmd (ft_execve)
int execute_single_cmd(t_data *data, int builtin_flag) 
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
			ft_execve(data, FIRST_CMD);
			return (FAILURE); //			
		}		
	}
	else
	{
		waitpid(chlpid, &wstatus, 0); //wait(&wstatus);	
		return (SUCCESS);
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
/*
* Só fiz a SINGLE EXEC. Parei para resolver o problema do exit: Saí depois de umas vezes, apenas
*
*
*/

void single_exec(t_data *data) // [ok]
{
	int	  builtin_flag;
	
	builtin_flag = is_builtins(data->argve[FIRST_CMD][0]);
	if (builtin_flag == EXIT) //Exit n forka, sai direto
		mini_exit(data);
	else
		execute_single_cmd(data, builtin_flag);
}


//FALTA IMPLEMENTAR!::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int multiple_exec(t_data *data)
{
	int id;
	int builtin_flag;
    int fd[data->number_of_pipes][2];
    int pid[data->number_of_pipes + 1];

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
			//signal(SIGINT, SIG_DFL);			
			scope_pipe_select(id, data->number_of_pipes, fd);//aqui entra redir			
			builtin_flag = is_builtins(data->argve[id][0]);
			if (builtin_flag)
			{
				builtin_exec(data, builtin_flag);
				exit (SUCCESS);//sai ok, n forka mais
			}
			else
			{
				ft_execve(data, id);
				exit (FAILURE); //sai ok, n forka mais			
			}
		}
		id++;
	}
	main_process_handler(pid, data->number_of_pipes, fd);	
	return SUCCESS;//tratar erros		

	//int pipefd[2];
	//int index;
	//int	  builtin_flag;
	//pid_t p1;
	//pid_t p2;
//
	//index = 0;
	//if (pipe(pipefd) < 0)
	//{
	//	printf("\nPipe could not be initialized\n");
	//	return;
	//}
	//p1 = fork();
	//builtin_flag = is_builtins(data->argve[index][0]);
	//if (p1 < 0)
	//{
	//	printf("\nCould not fork\n");
	//	return;
	//}
	//if (p1 == 0)
	//{
	//	close(pipefd[0]);
	//	dup2(pipefd[1], STDOUT_FILENO);
	//	close(pipefd[1]);
//
	//	if (builtin_flag)
	//		builtin_exec(data, builtin_flag);
	//	else if (execvp(data->argve[index][0], data->argve[0]) < 0) //n vai rodar
	//	{
	//		printf("\nCould not execute command 1..\n");
	//		exit(0);
	//	}
	//}
	//else
	//{
	//	index++;
	//	p2 = fork();
	//	builtin_flag = is_builtins(data->argve[index][0]);
	//	if (p2 < 0)
	//	{
	//		printf("\nCould not fork\n");
	//		return;
	//	}
	//	if (p2 == 0)
	//	{
	//		close(pipefd[1]);
	//		dup2(pipefd[0], STDIN_FILENO);
	//		close(pipefd[0]);
	//		if (builtin_flag)
	//			builtin_exec(data, builtin_flag);
	//		else if (execvp(data->argve[index][0], data->argve[1]) < 0) //n vai rodar
	//		{
	//			printf("\nCould not execute command 2..\n");
	//			exit(0);
	//		}
	//	}
	//	else
	//	{
	//		wait(NULL);
	//		wait(NULL);
	//	}
	//}
}







