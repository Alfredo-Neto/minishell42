/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:00 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/07 00:30:54 by ebresser         ###   ########.fr       */
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

int redir_execute_pid(t_data *data, int id) //file_redirect_fds(t_data *data, int id) //, int n_pipes, int fd[n_pipes][2])
{
    //Para teste abre
    data->outfile = (char **)malloc(sizeof(char *) * 4);
    printf("Está sendo redirecionado a arquivo! Arquivo criado: ver pasta testes\n");
    data->outfile[0] = "./testes/file_a.txt";// >
    data->outfile[1] = "./testes/file_b_append.txt";//
    data->outfile[2] = "./testes/file_c.txt";//
    data->outfile[3] = NULL;
    int file_no = ft_str_count(data->outfile);    
    data->outfile_mode = (int *)malloc(sizeof(int) * file_no);
    data->outfile_mode[0] = 1;
    data->outfile_mode[1] = 2;
    data->outfile_mode[2] = 1;
    //---para teste fecha

    //vou fazer tudo de novo ->novos filhos
    // CASO 1: > e >> (Só muda se abre append ou normal)
    //ex: echo oi > a >> b > c
    //echo oi > a
    //echo oi >> b //append
    //echo oi > c
    int file_id; //pid
    int pid[file_no];
    int fd_current_file;

    file_id = 0;
    if (data->outfile) //tenho outfiles
    {
        while(file_id < file_no) //miniprocessos
        {
            pid[file_id] = fork();
            if (pid[file_id] < 0)
            {
                perror("fork");
			    return FAILURE;
            }
            if (pid[file_id] == 0)
            {
                if (data->outfile_mode[file_id] == 1)
                    fd_current_file = open(data->outfile[file_id], O_WRONLY | O_CREAT , 0777);
                else if (data->outfile_mode[file_id] == 2)
                    fd_current_file = open(data->outfile[file_id], O_WRONLY | O_CREAT | O_APPEND, 0777);
                if (fd_current_file == -1)
                {
                    perror("open error");
                    return FAILURE;
                }
                dup2(fd_current_file, STDOUT_FILENO);
                close(fd_current_file);
                execute_pid(data, id);
            }
            file_id++;
        }
    }
    free(data->outfile);//teste
    free(data->outfile_mode);//teste
    return SUCCESS;
}