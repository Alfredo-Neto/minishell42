#include "../../minishell.h"

void echo(char **parsed_str)
{
    int break_line;

    break_line = true;

    if (parsed_str[0])
    {
        if (!ft_strncmp(*parsed_str, "-n", 3))
        {
            break_line = false;
            parsed_str++;
        }
        while (*parsed_str)
        {
            ft_putstr_fd(*parsed_str, 1);
            ft_putchar_fd(' ', 1);
            parsed_str++;
        }
        if (break_line)
            ft_putstr_fd("\n", 1);
    }
    else
        ft_putstr_fd("\n", 1);
}