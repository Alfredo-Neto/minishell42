/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:20:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/12 22:20:41 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
void	remove_extra_cases(t_data *data)
{
	int	id;
	int	i;
	int	j;

	id = 0;
	while (id < data->number_of_pipes + 1)
	{
		i = 0;
		while (*argve[i])
		{
			if (ft_strchr(*argve[i], '=') && \
				ft_str_count(*argve) > 1)
			{
				search_more_attributions(data, &id, &i);
				break ;
			}
			i++;
		}
		id++;
	}
}

void	search_more_attributions(t_data *data, int *id, int *i)
{
	int	j;

	j = *i;
	while (data->argve[*id][j])
	{
		if (!ft_strchr(data->argve[*id][j], '='))
		{
			*i = delete_ptrs(data, *i);
			if (*id)
				*id = delete_proccesses(data, *id);
			else
				(*id)++;
			return ;
		}
	}
}

int	delete_ptrs(t_data *data, int i)
{
	int	c;

	c = 0;
	while (c < i)
	{
		
	}
}

int	delete_proccesses(t_data *data, int id)
{
	int	c;

	c = 0;
	while (c < id)
	{
		
	}
	data->number_of_pipes--;
}
*/
