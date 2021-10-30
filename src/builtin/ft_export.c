/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:45:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/29 17:21:16 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_env_reassigned_check(t_var *var, char *name,
					char *content, int equal)
{
	t_envar	*tmp;

	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 1 && equal == 1)
		{
			tmp->content = content;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export_export_reassigned_check(t_var *var, char *name,
					char *content, int equal)
{
	t_envar	*tmp;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 1 && equal == 1)
		{
			tmp->content = content;
			return (-1);
		}
		else if (ft_strcmp(tmp->name, name) == 1 && equal == 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	export_env_insert(t_var *var, char *name, char *content)
{
	int		size;
	t_envar	*tmp;
	t_envar	*tmp2;

	tmp = var->envar;
	tmp2 = var->envar;
	size = 0;
	tmp = ft_envar_new(name, content);
	size = ft_envarsize(tmp2);
	if (envar_insert(&var->envar, tmp, size) == 1)
		return (0);
	return (0);
}

int	cmd_export_insert(t_var *var, char *name, char *content, int equal)
{
	t_envar	*new;
	t_envar	*tmp2;
	int		pos;

	tmp2 = var->export;
	// if (tmp->next != FALSE)
	// 	str = tmp->next->content;
	if (equal == 0)
	{
		new = ft_envar_new(name, 0);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	else
	{
		new = ft_envar_new(name, content);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	return (0);
}

int	ft_export(t_var *var)
{
	int		i;
	char	*name;
	char	*content;
	int		equal;
	int		j;

	if (cmd_export_alone(var) == 1)
		exit (0);
	j = 1;
	while (var->input->args[j])
	{
		i = 0;
		equal = 0;
		if (unset_export_error_handling(var, var->input->args[j]) != -1)
		{
			name = (char *)malloc(sizeof(ft_strlen(var->input->args[j]) + 1));
			content = (char *)malloc(sizeof(ft_strlen(var->input->args[j]) + 1));
			name = export_name_equal_search(var->input->args[j], &i, &equal, name);
			content = export_content_search(&i, var->input->args[j], content);
			i = export_env_reassigned_check(var, name, content, equal);
			if (equal == 1 && i != -1)
				export_env_insert(var, name, content);
			if (export_export_reassigned_check(var, name, content, equal) != -1)
				cmd_export_insert(var, name, content, equal);
		}
		j++;
	}
	exit (0); // bien penser a free ici
}
