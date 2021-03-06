/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:30:51 by ocarlos-          #+#    #+#             */
/*   Updated: 2022/05/02 23:20:23 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// list handling functions

// creates a new node with received values
t_vars	*new_node(char *name, char *value)
{
	t_vars	*new;

	new = (t_vars *)malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->var_name = ft_strdup(name);
	new->var_value = ft_strdup(value);
	new->next = NULL;
	new->env = -1;
	return (new);
}

// finds the last node on the list
t_vars	*last_in_list(t_vars *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// creates a new node on an existing list
void	add_to_list(t_vars **lst, char *name, char *value)
{
	t_vars	*aux;
	t_vars	*new;

	new = new_node(name, value);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = last_in_list(*lst);
	aux->next = new;
}

// clears the list and frees its memory
void	clear_list(t_vars *lst)
{
	t_vars	*aux;

	if (lst != 0x0)
	{
		while (lst)
		{
			aux = lst->next;
			free(lst->var_name);
			free(lst->var_value);
			free(lst);
			lst = aux;
		}
	}
}

// finds a variable name on a list
//char	*find_in_list(char *var_name, t_vars *lst)
t_vdt	find_in_list(char *var_name, t_vars *lst)
{
	t_vdt	ret;

	ret = (t_vdt){0};
	if (!(++var_name))
	{
		ret.value = "$";
		return (ret);
	}
	var_name--;
	if (lst != 0x0)
	{
		while (lst)
		{
			if (ft_strcmp(var_name, lst->var_name) == 0)
			{
				ret.value = lst->var_value;
				ret.is_envp = lst->env;
				return (ret);
			}
			lst = lst->next;
		}
	}
	ret.value = "$";
	return (ret);
}

// changes the value of an existing variable on the list
void	change_in_list(t_vars *lst, char *var_name, char *var_value)
{
	if (lst != 0x0)
	{
		while (lst)
		{
			if (ft_strcmp(var_name, lst->var_name) == 0)
			{
				free(lst->var_value);
				lst->var_value = ft_strdup(var_value);
				return ;
			}
			lst = lst->next;
		}
	}
}

// deletes an item in list
void	delete_in_list(char *var_name, t_vars **vars)
{
	t_vars	*temp;
	t_vars	*prev;

	temp = *vars;
	if (temp && !ft_strcmp(var_name, temp->var_name))
	{
		*vars = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		return ;
	}
	while (temp && ft_strcmp(var_name, temp->var_name))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp->var_name);
	free(temp->var_value);
	free(temp);
}

// updates the envp index in a list item
void	upd_idx_in_list(t_vars *lst, char *var_name, int pos)
{
	if (lst != 0x0)
	{
		while (lst)
		{
			if (ft_strcmp(var_name, lst->var_name) == 0)
			{
				lst->env = pos;
				return ;
			}
			lst = lst->next;
		}
	}
}
