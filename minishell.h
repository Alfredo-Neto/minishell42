/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/06 21:57:18 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
  
#define SUCCESS		0
#define FAILURE		1

#define CONTINUE	1
#define	STOP		0

#define FALSE		0
#define TRUE		1
#define GARBAGE		-1

#define FIRST_CMD	0
#define NO_PIPE		0
#define WITH_PIPE	1

#define NUMBER_OF_BUILTINS 5

#define EXIT		1
#define CD			2
#define ECHO		3
#define HELLO		4
#define HELP		5
#define	NONE		0






// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")


typedef struct	s_data
{    
	char	*input;
	char	**cmds_piped;
	char	***argve; //(cmd + args: argumento de execve)
	char	**envp; //colocar global?
	char	**command_path;
	int		number_of_pipes;
	int		exec_flag;
	int		exec_mode;
	int		exit_flag;
	int		tirar;
}				t_data;

//..................................................CORE
//data_handler.c
void	init_data(t_data *data);
int		init_command_path(t_data *data);
void	data_clean(t_data *data);
void	free_cmds_piped(t_data *data);
void	free_command_path(t_data *data);
void	free_argve(t_data *data);

//minishell.c
void	minishell(t_data *data);

//..................................................PROMPT
//prompt_take_input.c
int		take_input(t_data *data);
void	print_dir(void); //Faremos pwd?
//void prompt() FAZER

//history.c
void	put_on_history(char *buf, char *old_input);

//..................................................LEX
//lexer.c - tokens
void	lexer (t_data *data);
void	pull_pipe(t_data *data); //, char ***cmds_piped);
void	pull_space(t_data *data); //), char ***cmds_piped);

//..................................................PARSE
//parser.c  -  quotes ok: analisa!
void	parser(t_data *data);
//parse_quotes();
//parse_redirects();

//..................................................EXPANDER
//expand_variables.c
void expand_vars(t_data *data);

//..................................................EXEC
//sorting.c
int		is_builtins(char *cmd);
void	exec_selector(t_data *data);


//executor.c
void	executor(t_data *data);
void	ft_execve(t_data *data, int argve_index);
int		execute_single_cmd(t_data *data, int builtin_flag);
int		multiple_exec(t_data *data);
void 	single_exec(t_data *data);
void	builtin_exec(t_data *data, int code);

//pipes_fds_handling.c 
int		open_pipes(int n_pipes, int fd[n_pipes][2]);
int		close_pipes(int id, int n_pipes, int fd[n_pipes][2]);
int		stdin_stdout_redirect(int in, int out);
int		file_descriptor_handler(int id, int n_pipes, int fd[n_pipes][2]);
int		scope_pipe_select(int id, int n_pipes, int fd[n_pipes][2]);

//processes_handler.c
int		main_process_handler(int *pid, int n_pipes, int fd[n_pipes][2]);

//..................................................BUILTINS
//exit.c
int		exit_minishell(t_data *data, int status);
void	mini_exit (t_data *data);

//help.c
void	open_help(void);

//echo.c
void	echo(t_data *data);

//hello.c
void	hello(void);


//..................................................TOOLS
// str_tools.c
int		ft_strcpy_handled(char **new, char const *src);
int		ft_strjoin_handled(char **s1, char const *s2);
int		ft_str_count(char **str);

//////////////////////////////////////////////////////////

void	welcome(void);

#endif
