/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:29:54 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/13 16:44:57 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_export_error_handling(t_var *var)
{
	t_list	*tmp;
	int		i;
	
	i = 0;
	tmp = var->list;
	if (tmp->next == 0)
		return (-1);
	while (tmp->next->content[i])
	{
		if (tmp->next->content[i] == '=' && tmp->next->content[0] != '=')
			return (0);
		else if (!ft_isalnum(tmp->next->content[i]) || ft_isdigit(tmp->next->content[0]))
		{
			write (2, "minishell: ", 12);
			write(2, tmp->content, ft_strlen(tmp->content));
			write (2, ": `", 3);
			write(2, tmp->next->content, ft_strlen(tmp->next->content));
			ft_putendl_fd("': not a valid identifier", 2);
			return (-1);
		}
		i++;
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
	t_envar	*tmp;
	int		pos;

	pos = 0;
	tmp = var->envar;
	var->cmd = &(var->cmd[6]);
	if (unset_export_error_handling(var) == -1)
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
