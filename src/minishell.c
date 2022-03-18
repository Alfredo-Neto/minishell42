#include "../minishell.h"

void minishell(t_data *data)
{
    take_input(data->input_string);
    printf(".......................INPUT: %s\n", data->input_string);
    data->exec_flag = process_string(data->input_string, data->parsed_args,
                                    data->parsed_args_piped);
    if (data->exec_flag == 1)
        exec_args(data->parsed_args);
    if (data->exec_flag == 2)
        exec_args_piped(data->parsed_args, data->parsed_args_piped);
}