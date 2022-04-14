/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:30 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/13 21:08:35 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell(t_data *data)
{
	signal(SIGINT, new_prompt_mini);
	signal(SIGTERM, SIG_IGN);

	data_clean(data);
	take_input(data);
	lexer(data); // analise lexica - tokens - apenas divisao
	//parser(data) - analise sintatica - quotes, redirects, etc
	//expander(data) - vars
	executor(data);
}