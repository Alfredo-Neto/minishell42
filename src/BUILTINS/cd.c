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

static char *trim_backwards_until_slash(char *absolute_path)
{
    size_t i;

    i = ft_strlen(absolute_path);
    while (absolute_path[i] != '/')
        i--;
    absolute_path = ft_substr(absolute_path, 0, i + 1);
    return (absolute_path);
}

static char **trim_off_current_dir(char **directory)
{
    char absolute_path[CHAR_MAX_NUM];

    getcwd(absolute_path, sizeof(absolute_path));
    *directory = trim_backwards_until_slash(absolute_path);
    return (directory);
}

static char **parse_directory(char **directory)
{
    char **trimmed_directory;

    if (ft_strncmp(*directory, "../", 3))
        return (directory);
    else
    {
        trimmed_directory = trim_off_current_dir(directory);
        return (trimmed_directory);
    }
}

int cd(t_data *data)
{
    char **directory;

    (void)directory;
    if (!data->argve[0] || too_many_arguments(data->argve[0]))
        return (EXIT_FAILURE);
    directory = parse_directory(&(data->argve[0][1]));
    if (chdir(*directory))
    {
        ft_putstr_fd("cd: ", 1);
        perror(*directory);
        // free stuff out
        return (EXIT_FAILURE);
    }
    // update_env_pwd
    // free stuff out
    return (EXIT_SUCCESS);
}
