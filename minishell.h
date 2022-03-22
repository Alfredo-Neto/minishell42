/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/22 13:44:19 by ebresser         ###   ########.fr       */
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
  
#define SUCCESS		0
#define FAILURE		1

#define FALSE		0
#define TRUE		1

#define NO_PIPE		0

#define NO_BUILTINS 5

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
	char	***argve; //(cmd + args: argumento de execve)
	char	**envp; //colocar global?
	int		no_pipes;
	int		exec_flag;
	int		tirar;
}				t_data;

//..................................................CORE
//data_handler.c
void	init_data(t_data *data);
void	data_clean(t_data *data);

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
char	**pull_pipe(t_data *data);
void	pull_space(t_data *data, char **cmds_piped);

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
int		is_builtins(t_data *data);
void	exec_selector(t_data *data);
void	system_exec(t_data *data);

//executor.c
void	executor(t_data *data);
void	multiple_exec(t_data *data);
void 	single_exec(t_data *data);
void	builtin_exec(t_data *data, int code);

//..................................................BUILTINS
//exit.c
int		exit_minishell(t_data *data, int status);

//help.c
void	open_help(void);

//echo.c
void	echo(t_data *data);

//hello.c
void	hello(void);


//..................................................TOOLS
// Vamos usar funcoes proprias
int		ft_strcpy_handled(char **new, char const *src);
int		ft_str_count(char **str);
void	free_str(char *str);
void	free_double_str(char **str);
void	free_triple_str(char ***str);

//////////////////////////////////////////////////////////

void	welcome(void);

#endif
