#include "../../minishell.h"

static int too_many_arguments(char **str)
{
    if (str && str[1] && str[2])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static char *get_dir(char *directory)
{

    return (directory);
}

int cd(t_data *data)
{
    char *directory;

    (void)directory;
    if (!data->argve[0] || too_many_arguments(data->argve[0]))
        return (EXIT_FAILURE);
    directory = get_dir(data->argve[0][1]);
    if (chdir(directory))
    {
        ft_putstr_fd("cd: ", 1);
        perror(directory);
        free_str(directory);
        return (EXIT_FAILURE);
    }
    // update_env_pwd
    // free stuff out
    return (EXIT_SUCCESS);
}

void free_double_str(char ***str) // Uso: passar endereço da **str
{
    char **aux;
    int i = 0;

    aux = *str;
    if (str && *str)
    {
        while (aux[i])
            free(aux[i++]);
        free(aux);
    }
}