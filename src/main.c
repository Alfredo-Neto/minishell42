/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:08:49 by joeduard          #+#    #+#             */
/*   Updated: 2022/04/19 21:32:16 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	welcome(void)
{
	char	*username;

	clear();
	username = getenv("USER");
	printf("\e[32m*******************************************\e[39m\n");
	printf("\e[32m|                                         |\e[39m\n");
	printf("\e[32m|             MINISHELL  v1.0             |\e[39m\n");
	printf("\e[32m|                                         |\e[39m\n");
	printf("\e[32m*******************************************\e[39m\n");
	printf("\n\n\n\e[32mHi, @%s!\e[39m\n\n", username);
}


int	main(int argc, char **argv, char **envp)
{
	t_data *data;
	
	if (argc > 1 && *argv)
	{
		ft_putendl_fd("Minishell: Too many arguments", 1);
		return (FAILURE);
	}
	data = (t_data *)malloc(sizeof(t_data));
	welcome();
	init_data(data);
	data->envp = envp;	
	while (!data->exit_flag) //Resolver questão exit	
		minishell(data);		
	return 0;
}
	
