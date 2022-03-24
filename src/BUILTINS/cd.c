#include "../../minishell.h"

static char *trim_backwards_until_slash(char **absolute_path)
{
    size_t i;

    printf("DENTRO DO TRIM %s\n", *absolute_path);
    i = ft_strlen(*absolute_path);
    while ((*absolute_path)[i] != '/')
    {
        printf("DENTRO DO WHILE\n");
        i--;
    }
    *absolute_path = ft_substr(*absolute_path, 0, i + 1);
    printf("ABS %s\n", *absolute_path);
    return (*absolute_path);
}

static char **trim_off_current_dir(char **directory)
{
    printf("DIR %s\n", *directory);
    char *absolute_path;
    if (absolute_path == NULL)
    {
        printf("DENTRO DO ELSE %s\n", absolute_path);
        absolute_path = "PWD";
        absolute_path = getenv(absolute_path);
        *directory = trim_backwards_until_slash(&absolute_path);
    }
    else
    {
        printf("DENTRO DO IF %s\n", absolute_path);
        *directory = trim_backwards_until_slash(&absolute_path);
    }
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

int cd(char **directory)
{
    int ret;

    ret = 0;
    directory = parse_directory(directory);
    ret = chdir(*directory);
    return (ret);
}
