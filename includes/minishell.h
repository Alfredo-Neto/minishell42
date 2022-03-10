#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
  
#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
  
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

#define NO_BUILTINS 4

//init minishell
void init_shell();
int takeInput(char* str);
void printDir();
void execArgs(char** parsed);
void execArgsPiped(char** parsed, char** parsedpipe);
void openHelp();
int ownCmdHandler(char** parsed);
int parsePipe(char* str, char** strpiped);
void parseSpace(char* str, char** parsed);
int processString(char* str, char** parsed, char** parsedpipe);



#endif
