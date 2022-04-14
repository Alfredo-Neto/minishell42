/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/13 21:46:33 by ebresser         ###   ########.fr       */
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
  
#define SUCCESS				0
#define FAILURE				1

#define FALSE				0
#define TRUE				1
#define GARBAGE				-1
#define NOT_EXIST			-2

#define	GREAT				1
#define GREATGREAT			2
#define LESS				3
#define LESSLESS			4

#define NUMBER_OF_BUILTINS	5

#define EXIT				1
#define CD					2
#define ECHO				3
#define HELLO				4
#define HELP				5
#define	NONE				0

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

typedef struct	s_data
{    
	char	**envp; //devemos alocar
	char	**command_path;// = envp[PATH]

	char	*input;
	char	**cmds_piped;
	char	***argve; //(cmd + args: argumento de execve)
	
	int		number_of_pipes;
	int		exec_flag;
	
	int		exit_flag;

	char	***file;
	char	**file_mode;
	
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

//signals.c
void	handler(int signal);
void	exec_signals(void);
void	new_prompt_mini(int signal);

//minishell.c
void	minishell(t_data *data);

//..................................................PROMPT
//prompt_take_input.c
int		take_input(t_data *data);
void	print_dir(void);
//void prompt() FAZER

//history.c
void	put_on_history(char *buf, char *old_input);

//..................................................LEX
//lexer.c - tokens
void	lexer (t_data *data);
void	pull_pipe(t_data *data); 
void	pull_space(t_data *data); 

//..................................................PARSE
//parser.c  -  quotes ok: analisa!
void	parser(t_data *data);

//..................................................EXPANDER
//expand_variables.c
void expand_vars(t_data *data);

//..................................................EXEC
//sorting.c
int		is_builtins(char *cmd);

//redirects.c
void	new_prompt_heredoc(int signal);
void	redirect(char *file, int flags, int std_fd);
void	heredoc(char *eof);
void	redirect_filter(t_data *data, int id);

//executor.c
int		executor(t_data *data);
int		execute_pid(t_data *data, int id);
void	ft_execve(t_data *data, int argve_index);
int		multiple_exec(t_data *data);
void	builtin_exec(t_data *data, int code);

//pipes_fds_handling.c 
int		open_pipes(int n_pipes, int fd[n_pipes][2]);
int		close_other_fds(int id, int n_pipes, int fd[n_pipes][2]);
int		stdin_stdout_handler(int in, int out);
int		file_descriptor_handler(int id, int n_pipes, int fd[n_pipes][2]);
int		scope_fd_select(int id, int n_pipes, int fd[n_pipes][2]); 
int		redir_execute_pid(t_data *data, int id); 

//processes_handler.c
int		main_process_handler(int *pid, int n_pipes, int fd[n_pipes][2]);

//..................................................BUILTINS
//exit.c
int		exit_minishell(t_data *data, int status);
void	check_exit(t_data *data);
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
