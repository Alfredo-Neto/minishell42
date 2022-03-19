#include "../../minishell.h"

static char *trim_backwards_until_slash(char *absolute_path)
{
    size_t i;

    i = ft_strlen(absolute_path);
    while (absolute_path[i] != '/')
        i--;
    return (ft_substr(absolute_path, 0, i + 1));
}

static char **trim_off_current_dir(char **directory)
{
    char *absolute_path;
    absolute_path = ft_strdup("");
    absolute_path = "/home/alfredo/42-projects/minishell42";

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

int cd(char **directory)
{
    int ret;

    ret = 0;
    directory = parse_directory(directory);
    ret = chdir(*directory);
    return (ret);
}
