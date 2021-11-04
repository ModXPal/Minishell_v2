/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:45:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/02 17:50:11 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_env_reassigned_check(t_var *var, int equal)
{
	t_envar	*tmp;

	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var->name) == 1 && equal == 1)
		{
			tmp->content = var->content;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export_export_reassigned_check(t_var *var, int equal)
{
	t_envar	*tmp;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var->name) == 1 && equal == 1)
		{
			tmp->content = var->content;
			return (-1);
		}
		else if (ft_strcmp(tmp->name, var->name) == 1 && equal == 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	export_env_insert(t_var *var)
{
	int		size;
	t_envar	*tmp;
	t_envar	*tmp2;

	tmp = var->envar;
	tmp2 = var->envar;
	size = 0;
	tmp = ft_envar_new(var->name, var->content);
	size = ft_envarsize(tmp2);
	if (envar_insert(&var->envar, tmp, size) == 1)
		return (0);
	return (0);
}

void	export_execution(t_var *var, char *args)
{
	var->content = 0;
	var->name = 0;
	if (unset_export_error_handling(var, args) != -1)
		exec_export(var, args);
	// if (var->name)
	// {
	// 	free (var->name);
	// }
	// if (var->content && equal == 1)
	// {
	// 	free (var->content);
	// }
}

int	ft_export(t_var *var)
{
	int		j;

	var->error = 0;
	j = 1;
	if (cmd_export_alone(var) == 1)
	{
		g_exit_status = 0;
		exit (g_exit_status);
	}
	while (var->input->args[j])
	{
		export_execution(var, var->input->args[j]);
		j++;
	}
	g_exit_status = 0;
	if (var->error == 1)
		g_exit_status = 1;
	exit (g_exit_status);
}
