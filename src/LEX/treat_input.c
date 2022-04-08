/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:55:15 by azamario          #+#    #+#             */
/*   Updated: 2022/04/08 03:31:09 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	treat_input(t_data *data)			// echo "'jorge' ale"
{	
	printf("0. input : %s\n", data->input);

	//adicionar o validate input											
	treat_input_chars(data->input); 			// echo "'jorge'1ale"  - > se entre as aspas tiver ' ' ou > ou  < ou |, substitui por um char não imprimível
	data->tokens = tokenizer(data->input);		// echo\0 "'jorge'1ale"\0 	->quebra os inputs em tokens para tratar, o que estiver entre aspas será um token único: "'jorge'1ale"
	print_token(data->input);					//	debug
	treat_token_list(data->tokens);				//	coloca tokens em variável temporária dentro de nova struct | trata quotes-dollar-no quotes-reverse_input_chars
	data->input = restore_command_line(data->tokens);
}
