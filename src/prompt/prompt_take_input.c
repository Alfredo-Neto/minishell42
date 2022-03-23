/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_take_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:56:26 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/17 18:33:46 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// Function to print Current Directory.
void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

/** Function to take input */
int	take_input(char *input)
{
	char	*buf;
	char	*old_input;
	char	*prompt;
	
	prompt = "Concatenar User:Dir$ ";//criar func
	old_input = input;
	buf = readline(prompt);
	if (strlen(buf) != 0)
	{
		put_on_history(buf, old_input);
		strcpy(input, buf);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}