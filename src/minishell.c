
#include "../includes/minishell.h"

// Greeting shell during startup
void init_shell()
{
    clear();
    printf("\n\t****MY SHELL****\n");
    printf("\n\t-USE AT YOUR OWN RISK-\n");
    printf("\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(10);
    clear();
}

// Function to take input
int takeInput(char* str)
{
    char* buf;
  
    buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    init_shell();
    return (0);
}