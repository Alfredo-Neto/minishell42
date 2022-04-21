/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:54:50 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/21 12:50:45 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Vamos usar funcoes proprias
/* DICA: Usar "new" como argumento onde este é alocado
* para mapeamento de leak
*/
int ft_strcpy_handled(char **new, char const *src)
{
	size_t	len;
	int		i;

	len = ft_strlen(src);
	if (!*new)
		*new = (char *)malloc(len * sizeof(char) + 1);
	if (!*new)
	{
		perror("malloc error");
		return (FAILURE);
	}
	i = 0;
	while (src[i])
	{
		(*new)[i] = src[i];
		if (src[i])
			i++;	
	}
	(*new)[i] = '\0';
	return (SUCCESS);
}

//conta strings em char**
int	ft_str_count(char **str)
{
	int count;

	count = 0;
	if (str)
	{
		while(str[count])
			count++;
	}
	return (count);
}

static void	copylen(char *scpy, const char *s)
{
	int	i;

	if (!s || ft_strlen(s) > ft_strlen(scpy))
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		scpy[i] = s[i];
		i++;
	}
}

int		ft_strjoin_handled(char **s1, char const *s2) 
{ //tratada: libera string antiga - adiciona s2 ao final de s1
	size_t	len;
	size_t	k;
	char	*s;

	if (!*s1 || !s2)
		return FAILURE;
	len = ft_strlen(*s1) + ft_strlen(s2) + 1;
	if (!(s = (char*)malloc(len * sizeof(char))))
		return FAILURE;
	copylen(s, *s1);
	k = ft_strlen(*s1);
	copylen(&s[k], s2);
	k = k + ft_strlen(s2);
	s[k] = '\0';
	free(*s1); //desprezo s1 antiga
	*s1 = s;
	return SUCCESS;
}
