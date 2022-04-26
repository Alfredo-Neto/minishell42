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

int isInvalidArgs(t_data *data)
{
    if (!data->argve[0] || too_many_arguments(data->argve[0]))
        return (1);
    return (0);
}

static char *get_dir(char **str)
{

    return ();
}

int cd(t_data *data)
{
    char **new_dir;
    char *old_dir;
    char *curr_dir;

    if (isInvalidArgs(data))
        return (EXIT_FAILURE);
    new_dir = data->argve[0][1];
    old_dir = get_current_dir();
    if (chdir(new_dir))
    {
        ft_putstr_fd("cd: ", 1);
        perror(new_dir);
        ft_super_free((void *)&new_dir);
        return (EXIT_FAILURE);
    }
    curr_dir = get_current_dir()
    update_env_vars("PWD");
    update_env_vars("OLDPWD");
    ft_super_free((void *)&new_dir);
    ft_super_free((void *)&old_dir); 
    ft_super_free((void *)&curr_dir); 
    return (EXIT_SUCCESS);
}

// alt_cd
//     too_many_arguments
//         get_dir
//             get_current_dir
//                 update_env_dir

//                     HOME
//                         envp
//                             set_env