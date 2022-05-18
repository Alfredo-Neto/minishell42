/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:08:58 by azamario          #+#    #+#             */
/*   Updated: 2022/05/17 23:25:37 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir)
		printf("%s\n", dir);
	free(dir);
	g_status_code = 0; //
}
