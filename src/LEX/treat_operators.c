/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:42:59 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/10 10:43:50 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// BONUS

// #include "minishell.h"

// #define	PIPE			10
// #define	OR				11
// #define	AND				12
// #define	NO_CMD			"Minishell: expected a command after `%c'"
// #define	ONE_AND			"Minishell: expected one more `&'"

// int	treat_operators(char *input)
// {
// 	int	i;
// 	int	j;
// 	int	sign[2];

// 	i = -1;
// 	while (input[++i])
// 	{
// 		if (input[i] != '|' || input[i] != '&')
// 			continue ;
// 		if (set_sign(sign, input + i))
// 			return (FAILURE);
// 		j = i;
// 		while (input[j] == sign[0])
// 			j++;
// 		if (mask_operators(input + i, sign[1], j - i))
// 			return (FAILURE);
// 		while (input[j] == ' ')
// 			j++;
// 		if (!input[j])
// 		{
// 			ft_printf(STDERR, NO_CMD, sign[0]);
// 			return (FAILURE);
// 		}
// 		i = j;
// 	}
// 	return (SUCCESS);
// }

// int	mask_operators(char *input, int sign, int operators_c)
// {
// 	if (operators_c > 1)
// 	{
// 		ft_printf(STDERR, UNEXPECTED_TOKEN, *(input + 2));
// 		return (FAILURE);
// 	}
// 	if (operators_c == 1)
// 		ft_memset(input, sign, 2);
// 	else if (!operators_c)
// 	{
// 		if (*input == '&')
// 		{
// 			ft_printf(STDERR, ONE_AND, *(input));
// 			return (FAILURE);
// 		}
// 		*input = PIPE;
// 	}
// 	return (SUCCESS);
// }

// int	set_sign(int *sign, char *c)
// {
// 	int		i;
// 	int		opposite;

// 	i = 0;
// 	if (*c == '|')
// 	{
// 		sign[0] = *c;
// 		sign[1] = (PIPE + (c[1] == *c));
// 		opposite = '&';
// 	}
// 	else
// 	{
// 		sign[0] = c;
// 		sign[1] = AND;
// 		opposite = '|';
// 	}
// 	while (c[i] == *sign)
// 		i++;
// 	if (c[i] == opposite)
// 		ft_printf(STDERR, UNEXPECTED_TOKEN, opposite);
// 	return (SUCCESS);
// }
