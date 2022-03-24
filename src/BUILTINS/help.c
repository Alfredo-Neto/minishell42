/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarlos- <ocarlos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:06:23 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/24 12:25:26 by ocarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// Help command builtin - retirar (ou não!)
void open_help(void)
{
	puts("\n***WELCOME TO MY SHELL HELP***\n"
		 "Copyright @ Suprotik Dey\n"
		 "-Use the shell at your own risk...\n"
		 "List of Commands supported:\n"
		 ">cd\n"
		 ">ls\n"
		 ">exit\n"
		 ">all other general commands available in UNIX shell\n"
		 ">pipe handling\n"
		 ">improper space handling\n");
	return;
}