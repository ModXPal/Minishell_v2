/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:29:54 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/12 16:12:28 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset_error_handling(t_var *var)
{
	t_list *tmp;

	tmp = var->list->next;
	if (ft_isalpha(tmp->content[0]) == FALSE)
	{
		write(2, tmp->content, ft_strlen(tmp->content));
		ft_putendl_fd(": not a valid identifier", 2);
		return (-1);
	}
	return (0);
}

int	ft_unset_export(t_var *var, char *str)
{
	t_envar	*tmp;
	int		pos;
	
	pos = 0;
	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 1)
		{
			pos = ft_envar_position(var->export, tmp->name);
			envar_remove(&var->export, pos);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_var *var)
{
	t_envar *tmp;
	int pos;
	
	pos = 0;
	tmp = var->envar;
	var->cmd = &(var->cmd[6]);
	if (unset_error_handling(var) == 1)
		return (-1);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var->cmd) == 1)
		{
			pos = ft_envar_position(var->envar, tmp->name);
			envar_remove(&var->envar, pos);
		}
		tmp = tmp->next;
	}
	ft_unset_export(var, var->cmd);
	return (0);
}
