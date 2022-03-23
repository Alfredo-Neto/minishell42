#include "../minishell.h"

static void	sighandler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void minishell(t_data *data)
{
    signal(SIGINT, sighandler);
    signal(SIGTERM, SIG_IGN);
    take_input(data->input_string);
    printf(".......................INPUT: %s\n", data->input_string);
    data->exec_flag = process_string(data->input_string, data->parsed_args,
                                    data->parsed_args_piped);
    if (data->exec_flag == NO_PIPE)
        exec_args(data->parsed_args);
    if (data->exec_flag == PIPE_PRESENT)
        exec_args_piped(data->parsed_args, data->parsed_args_piped);
}
