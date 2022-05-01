/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:50:20 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/27 21:48:37 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data, char **envp)
{
	int		i;

	i = 0;
	ft_bzero(data, sizeof(t_data));
	data->envp = (char **)ft_calloc(ft_str_count(envp) + 1, sizeof(char *));
	if (!data->envp)
		exit_minishell(data, FAILURE);
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			exit_minishell(data, FAILURE);
		i++;
	}
	init_command_path(data);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
}

void	init_command_path(t_data *data)
{
	int		i;
	t_vars	*temp;

	data->command_path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (data->command_path[i] != NULL)
	{
		if (ft_strjoin_handled(&(data->command_path[i]), "/") == FAILURE)
		{
			ft_putstr_fd("Init failed\n", 2);
			exit_minishell(data, FAILURE);
		}
		i++;
	}
	i = 0;
	while (data->envp[i])
	{
		grab_vars(data, data->envp[i]);
		temp = last_in_list(data->vars);
		temp->env = i++;
	}
}

void	data_clean(t_data *data)
{
	if (data->string)
		free(data->string);
	if (data->input)
		free(data->input);
	if (data->pid)
		free(data->pid);
	data->string = NULL;
	data->input = NULL;
	data->pid = NULL;
	double_free((void ***)&data->fd);
	double_free((void ***)&data->cmds_piped);
	double_free((void ***)&data->tokens);
	double_free((void ***)&data->file_mode);
	triple_free(&data->file, data->number_of_pipes + 1);
	triple_free(&data->argve, data->number_of_pipes + 1);
	data->number_of_pipes = GARBAGE;
	data->exec_flag = GARBAGE;
}

void	double_free(void ***ptr)
{
	int		i;

	i = 0;
	if (!*ptr)
		return ;
	while ((*ptr)[i])
	{
		if ((*ptr)[i])
			free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

void	triple_free(char ****ptr, int number_of_ids)
{
	int		id;
	int		cmd;

	if (!*ptr)
		return ;
	id = 0;
	while (id < number_of_ids)
	{
		if ((*ptr)[id])
		{
			cmd = 0;
			while ((*ptr)[id][cmd])
			{
				if ((*ptr)[id][cmd])
					free((*ptr)[id][cmd]);
				(*ptr)[id][cmd] = NULL;
				cmd++;
			}
			free((*ptr)[id]);
			(*ptr)[id] = NULL;
		}
		id++;
	}
	free(*ptr);
	*ptr = NULL;
}
