/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:29:54 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/21 15:32:30 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_export_error_handling(t_var *var, char *content)
{
	int		i;
	
	i = 1;
	if (var->input->args[1] == 0 || content[0] == 0)
		return (-1);
	if (content[0] == 0)
		return (-1);
	while (var->input->args[i])
	{
		if (var->input->args[i][0] == '=' && content[0] != '=')
			return (0);
		else if (!ft_isalnum(content[i]) || ft_isdigit(content[0]) 
			|| content[0] == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	unset_error_export_message(t_var *var, char *content)
{
	(void) content;
	write (2, "minishell: ", 12);
	write(2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": `", 3);
	write(2, var->input->args[1], ft_strlen(var->input->args[1]));
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	ft_unset_export(t_var *var, char *str, int *args_exist)
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
			(*args_exist) = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

int unset_search_and_remove(t_var *var, int *cmd_exist, char *content)
{
	t_envar	*tmp;
	int		pos;
	
	pos = 0;
	tmp = var->envar;
	if (unset_export_error_handling(var, content) != -1)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, content) == 1)
			{
				pos = ft_envar_position(var->envar, tmp->name);
				envar_remove(&var->envar, pos);
			}
			tmp = tmp->next;
		}
	}
	ft_unset_export(var, content, cmd_exist);
	return (0);
}

int	ft_unset(t_var *var)
{
	t_envar	*tmp;
	t_list	*tmp_list;
	int		pos;
	int		cmd_exist;
	int		i;

	pos = 0;
	i = 0;
	cmd_exist = 0;
	tmp_list = var->list;
	tmp = var->envar;
	if (var->input->args[i])
		i++;
	while (var->input->args[i])
	{
		cmd_exist = 0;
		unset_search_and_remove(var, &cmd_exist, var->input->args[i]);
		// if (cmd_exist == 0)
		// 	unset_error_export_message(var, var->input->args[i]);
		i++;
	}
	return (0);
}
