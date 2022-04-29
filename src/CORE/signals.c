/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:52:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/29 17:03:00 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	Creates a new prompt.
void	new_prompt_mini(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line(); //Como funciona?
	rl_redisplay(); //Como funciona?
}

//	Handling signals for child process.
void	handler(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	else if (signal == SIGTERM)
	{
		printf("Terminated\n");
		exit(131);
	}
	else
	{
		printf("Coredumped\n");
		exit(1);
	}
}

void	exec_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	signal(SIGQUIT, handler);
}
