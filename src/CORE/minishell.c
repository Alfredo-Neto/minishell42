/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:47:57 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/22 13:48:19 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void minishell(t_data *data)
{
	data_clean(data);
	take_input(data);//captura na estrutura data->input		
    lexer(data); //analise lexica - tokens - apenas divisao
	//parser(data);//analise sintatica - quotes, etc
	//expander(data);	//final do processo - alias
	executor(data); //triagem e execução
}