/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:50:36 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 18:09:06 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset_error_export_message(t_var *var, char *content)
{
	var->error = 1;
	write (2, "minishell: ", 12);
	write(2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": `", 3);
	write(2, content, ft_strlen(content));
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	ft_unset_export(t_var *var, char *str, int *args_exist)
{
	t_envar	*tmp;
	int		pos;

	pos = 0;
	tmp = var->export;
	while (ft_strcmp(tmp->name, str) != 1)
	{
		if (tmp->next && tmp != 0)
			tmp = tmp->next;
		else if (tmp->next == 0)
			return (0);
	}
	printf ("tmp->name == %s\n", tmp->name);
	if (ft_strcmp(tmp->name, str) == 1)
	{
		pos = ft_envar_position(var->export, tmp->name);
		envar_remove(&var->export, pos);
		(*args_exist) = 1;
	}	
	return (0);
}

int	unset_search_and_remove(t_var *var, int *cmd_exist, char *content)
{
	t_envar	*tmp;
	int		pos;

	pos = 0;
	tmp = var->envar;
	if (unset_export_error_handling(var, content) != -1)
	{
		while (ft_strcmp(tmp->name, content) != 1)
		{
			if (tmp->next)
				tmp = tmp->next;
			else if (tmp->next == 0)
				break ;
		}
		if (ft_strcmp(tmp->name, content) == 1)
		{
			pos = ft_envar_position(var->envar, tmp->name);
			envar_remove(&var->envar, pos);
		}
	}
	ft_unset_export(var, content, cmd_exist);
	return (0);
}

int	unset_execution(t_var *var)
{
	int		cmd_exist;
	int		i;

	i = 0;
	cmd_exist = 0;
	if (var->input->args[i])
		i++;
	while (var->input->args[i])
	{
		cmd_exist = 0;
		if (var->input->args[i][0] == 0)
			unset_error_export_message(var, var->input->args[i]);
		else
			unset_search_and_remove(var, &cmd_exist, var->input->args[i]);
		i++;
	}
	return (0);
}

int	ft_unset(t_var *var)
{
	var->error = 0;
	unset_execution(var);
	EXIT_STATUS = 0;
	if (var->error == 1)
		EXIT_STATUS = 1;
	return (EXIT_STATUS);
}
