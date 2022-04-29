/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeduard <joeduard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:09:01 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/29 16:11:16 by joeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_on_history(char *buf, char *old_input)
{
	if (!old_input || ft_strcmp(old_input, buf))
		add_history(buf);
}
