/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:59:45 by ebresser          #+#    #+#             */
/*   Updated: 2022/03/27 13:31:23 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void free_str(char **str) //Uso: passar endereço da str
{
	if (str)
    {
        if (*str)
        {
            free(*str);
            *str = NULL;
        }
        str = NULL;
    }
}

void free_double_str(char ***str) //Uso: passar endereço da **str
{
    if (str)
    {
        free_str(*str);
        *str = NULL;
    }    
}

void free_triple_str(char ****str) //Uso: passar endereço da ***str
{
    if (str)
    {
        free_double_str(*str);
        *str = NULL;
    }    
} 
*/

/*
https://pythontutor.com/visualize.html#code=%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%23include%20%3Cunistd.h%3E%0Avoid%20free_str%28char%20**str%29%20//Uso%3A%20passar%20endere%C3%A7o%20da%20str%0A%7B%0A%20%20%20%20if%20%28str%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20if%20%28*str%29%0A%20%20%20%20%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20free%28*str%29%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20*str%20%3D%20NULL%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%20%20str%20%3D%20NULL%3B%0A%20%20%20%20%7D%0A%7D%0A%0Avoid%20free_double_str%28char%20***str%29%20//Uso%3A%20passar%20endere%C3%A7o%20da%20**str%0A%7B%0A%20%20%20%20if%20%28str%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20free_str%28*str%29%3B%0A%20%20%20%20%20%20%20%20*str%20%3D%20NULL%3B%0A%20%20%20%20%7D%20%20%20%20%0A%7D%0A%0Avoid%20free_triple_str%28char%20****str%29%20//Uso%3A%20passar%20endere%C3%A7o%20da%20***str%0A%7B%0A%20%20%20%20if%20%28str%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20free_double_str%28*str%29%3B%0A%20%20%20%20%20%20%20%20*str%20%3D%20NULL%3B%0A%20%20%20%20%7D%20%20%20%20%0A%7D%20%0Aint%20main%28%29%20%7B%0A%20%20char%20*str0%3B%0A%20%20char%20*str1%3B%0A%20%20char%20**str2%3B%0A%20%20char%20***str3%3B%0A%20%20%0A%20%20str0%20%3D%20%28char%20*%29malloc%282*sizeof%28char%29%29%3B%0A%20%20str0%5B0%5D%20%3D%20'a'%3B%0A%20%20str0%5B1%5D%20%3D%20'%5C0'%3B%0A%20%20str1%20%3D%20%28char%20*%29malloc%282*sizeof%28char%29%29%3B%0A%20%20str1%5B0%5D%20%3D%20'a'%3B%0A%20%20str1%5B1%5D%20%3D%20'%5C0'%3B%0A%20%20str2%20%3D%20%28char%20**%29malloc%283*sizeof%28char%20*%29%29%3B%0A%20%20str2%5B0%5D%20%3D%20str0%3B%0A%20%20str2%5B1%5D%20%3D%20str1%3B%0A%20%20str2%5B2%5D%20%3D%20NULL%3B%0A%20%20str3%20%3D%20%28char%20***%29malloc%282*sizeof%28char%20**%29%29%3B%0A%20%20str3%5B0%5D%20%3D%20str2%3B%0A%20%20str3%5B1%5D%20%3D%20NULL%3B%0A%20%20free_triple_str%28%26str3%29%3B%0A%0A%20%20return%200%3B%0A%7D&cumulative=false&curInstr=26&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=cpp_g%2B%2B9.3.0&rawInputLstJSON=%5B%5D&textReferences=false
*/

void free_str(char **str) //Uso: passar endereço da str
{
	if(str && *str)
	{
		free(*str);
		*str = NULL;		
	}
}

void free_double_str(char ***str) //Uso: passar endereço da **str
{
	int j;

	j = 0;
	if (str && *str)
	{
		while(str[j])
		{
			free_str(str[j]);
			str[j] = NULL;
			j++;
		}
	}    
}

void free_triple_str(char ****str) //Uso: passar endereço da ***str
{
	int i;
	
	i = 0;
	if (str)
	{
		while(str[i])
		{
			free_double_str(str[i]);
			str[i] = NULL;
			i++;
		}
	}    
} 