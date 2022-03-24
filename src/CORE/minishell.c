/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:47:57 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/24 12:13:36 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

static void    sighandler(int signal)
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

	data_clean(data);
	take_input(data);//captura na estrutura data->input		
    lexer(data); //analise lexica - tokens - apenas divisao
	parser(data);//analise sintatica - quotes, etc
	expander(data);	//final do processo - alias
	executor(data); //triagem e execução
}
