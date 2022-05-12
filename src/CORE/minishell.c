/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:30 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/11 21:37:44 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	signal(SIGINT, new_prompt_mini);
	signal(SIGQUIT, SIG_IGN);
	data_clean(data);
	if (take_input(data) || lexer(data))
		return ;
	if (parser(data))
		return ;
	expander(data);
	executor(data);
}
