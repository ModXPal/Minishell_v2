/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:43:45 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/06 15:52:37 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_export_shlvl(t_var *var)
{
    t_envar     *tmp;
    char        *str1;
    int         i;

    tmp = var->export;
    str1 = 0;
    if (ft_strcmp(var->input->args[0], "./minishell") == 1)
    {
        str1 = ft_envar_find_content(tmp, "SHLVL");
        tmp = var->export;
        i = ft_atoi(str1);
        i = i + 1;
        str1 = ft_itoa(i);
	    while (tmp)
    	{
	    	if (ft_strcmp(tmp->name, "SHLVL"))
	    	{
		    	tmp->content = str1;
                break;
	    	}
		    tmp = tmp->next;
	    }
    }
    return (0);
}

int ft_env_shlvl(t_var *var)
{
    t_envar *tmp;
    char    *str;
    int     i;
    
    tmp = var->envar;
    str = 0;
    i = 0;
    if (ft_strcmp(var->input->args[0], "./minishell") == 1)
    {
        str = ft_envar_find_content(tmp, "SHLVL");
        tmp = var->envar;
        i = ft_atoi(str);
        i = i + 1;
        str = ft_itoa(i);
	    while (tmp)
    	{
	    	if (ft_strcmp(tmp->name, "SHLVL"))
	    	{
		    	tmp->content = str;
                break;
	    	}
		    tmp = tmp->next;
	    }
    }
    return (0);
}

int ft_init_shlvl(t_var *var)
{
    ft_env_shlvl(var);
    ft_export_shlvl(var);
    return (0);
}