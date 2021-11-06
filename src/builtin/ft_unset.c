/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:29:54 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/06 17:30:45 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int	unset_export_error_handling(t_var *var, char *content)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (var->input->args[1] == 0 || content[0] == 0)
		return (-1);
	if (content[0] == 0)
		return (-1);
	while (var->input->args[i])
	{
		if (var->input->args[i][0] == '=' && content[0] != '=')
			return (0);
		else if (ft_isdigit(content[0])
			|| content[0] == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		i++;
	}
	while (content[j])
	{
		if (ft_isalnum(content[j]) == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		j++;
	}
	return (0);
}

int	unset_error_export_message(t_var *var, char *content)
{
	(void) content;
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

int	unset_search_and_remove(t_var *var, int *cmd_exist, char *content)
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
	var->error = 0;
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
	EXIT_STATUS = 0;
	if (var->error == 1)
		EXIT_STATUS = 1;
	return (EXIT_STATUS);
}
