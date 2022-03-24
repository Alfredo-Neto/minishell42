/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_take_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:56:26 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/24 12:26:45 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//void prompt() FAZER
//{
//
//}

// Function to print Current Directory.
void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("Dir: %s\n", cwd);
}

/** Function to take input - MALLOC input*/
int	take_input(t_data *data)
{
	char	*buf;
	char	*old_input;
	char	*prompt;
	int		status;
	
	prompt = "Concatenar User:Dir$ ";//criar func
	buf = readline(prompt);
	if (strlen(buf) != 0)
	{
		old_input = data->input; 
		put_on_history(buf, old_input);	
		status = ft_strcpy_handled(&data->input, buf);
		if (status == FAILURE)
			exit_minishell(data, FAILURE);
		//free(buf); ---> acho q readline já faz isso
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
