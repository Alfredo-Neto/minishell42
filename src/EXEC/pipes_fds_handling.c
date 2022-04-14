/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/12 21:04:47 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

int open_pipes(int n_pipes, int fd[n_pipes][2])
{
	int id;
	int j;

	id = 0;
    while (id < n_pipes) //open pipes
    {
        if ((pipe(fd[id++])) < 0)
        {
			perror("pipe");
            j = 0;
            while (j < id)
            {
                close(fd[j][0]);					
                close(fd[j][1]);
                j++;
            }
            exit (FAILURE); //tratar?
        }        
    }
	return SUCCESS;
}

int close_other_fds(int id, int n_pipes, int fd[n_pipes][2])
{
	int j;
	
    j = 0;
    while (j < n_pipes)
    {
        if (j != id)
            close(fd[j][1]);
        j++;
    }				
    j = 0;    
    while (j < n_pipes)
    {
        if (j != id - 1)
            close(fd[j][0]);
        j++;
    }
	return SUCCESS; //tratar erros
}

int stdin_stdout_handler(int in, int out)
{
	if (in != NOT_EXIST)
    {
        dup2(in, STDIN_FILENO);
        close(in);
    }
    if (out != NOT_EXIST)
    {
        dup2(out, STDOUT_FILENO);
        close(out);
    }
	return SUCCESS; //tratar erros(dup)?
}

int file_descriptor_handler(int id, int n_pipes, int fd[n_pipes][2])
{
	int fd_in;
	int fd_out;

    fd_in = 0;
    fd_out = 0;
	if (id == 0) //FIRST_CMD
		fd_in = NOT_EXIST;
	if (id == n_pipes) //LAST_CMD
		fd_out = NOT_EXIST;
	if (fd_in != NOT_EXIST)
		fd_in = fd[id - 1][0];
	if (fd_out != NOT_EXIST)
		fd_out = fd[id][1];	
	stdin_stdout_handler(fd_in, fd_out);    //
    
	return SUCCESS; //tratar erros
}

int scope_fd_select(int id, int n_pipes, int fd[n_pipes][2]) //t_data *data, 
{
	close_other_fds(id, n_pipes, fd);    
	file_descriptor_handler(id, n_pipes, fd);    
	return SUCCESS; //tratar erros
}
