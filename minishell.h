/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:10:08 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/21 14:19:15 by ocarlos-         ###   ########.fr       */
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

#define FALSE		0
#define TRUE		1

#define NO_PIPE		0

#define NUMBER_OF_BUILTINS 5

#define EXIT		1
#define CD			2
#define ECHO		3
#define HELLO		4
#define HELP		5
#define	NONE		0


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

typedef struct	s_vdt
{
	char	*value;
	int		is_envp;
	int		is_malloc;
}				t_vdt;

typedef struct	s_vars
{
	char			*var_name;
	char			*var_value;
	int				env;
	int				is_malloc;
	struct s_vars	*next;
}				t_vars;

typedef struct	s_data
{    
	char	*input;
	char	***argve; //(cmd + args: argumento de execve)
	char	**envp; //colocar global?
	t_vars	*vars;
	int		number_of_pipes;
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

//parse_vars.c
char	*get_var_value(char *input, int parse);
char	*get_var_name(char *input);
void	update_envp(t_data *data, char* name, char* value, t_vdt vdt);
void	grab_vars(t_data *data, char *str, int parse);

//..................................................EXPANDER
//expand_variables.c
void expander(t_data *data);

//..................................................EXEC
//sorting.c
int		is_builtins(char *cmd);
void	exec_selector(t_data *data);


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
//str_tools.c
int		ft_strcpy_handled(char **new, char const *src);
int		ft_str_count(char **str);
void	free_str(char **str);
void	free_double_str(char ***str);
void	free_triple_str(char ****str);

//list_tools.c
t_vars	*new_node(char *name, char *value);
t_vars	*last_in_list(t_vars *lst);
void	add_to_list(t_vars **lst, char *name, char *value);
void	clear_list(t_vars *lst);
t_vdt	find_in_list(char *var_name, t_vars *lst);
void	change_in_list(t_vars *lst, char *var_name, char *var_value);
int		is_envp(char *name, t_vars *lst);

//////////////////////////////////////////////////////////

void	welcome(void);

#endif
