/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:28:30 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/26 14:31:02 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell(t_data *data)
{
	signal(SIGINT, new_prompt_mini); //Ctrl C
	signal(SIGTERM, SIG_IGN); //Ctrl D --SIGQUIT?
	data_clean(data);
	if (take_input(data) || lexer(data)) //analise lexica - tokens - apenas divisao
		return ;//captura na estrutura data->input
	parser(data); //analise sintatica - quotes, etc
	expander(data); //final do processo - alias
	executor(data); //triagem e execução
}
