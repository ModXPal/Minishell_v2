/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:04:04 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 18:53:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_export_reassignement(t_var *var, t_envar *tmp,
						char *content, int export_already_exist)
{
	char	*to_free;

	to_free = 0;
	to_free = tmp->content;
	tmp->content = content;
	if (to_free)
	{
		free (to_free);
		to_free = 0;
	}
	if (export_already_exist == 1)
	{
		free (var->export_name);
		var->export_name = 0;
	}
	return (-1);
}

int	export_export_reassigned_check(t_var *var, char *name,
					char *content, int export_already_exist)
{
	t_envar	*tmp;

	tmp = var->export;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 1 && var->equal_env == 1)
		{
			export_export_reassignement(var, tmp, content,
				export_already_exist);
			return (-1);
		}
		if (export_already_exist == 1 && var->equal_env == 0)
		{
			free (var->export_name);
			var->export_name = 0;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export_env_reassignement(t_var *var, t_envar *tmp,
					char *name, char *content)
{
	char	*to_free;

	to_free = 0;
	if (ft_strcmp(tmp->name, name) == 1)
	{
		to_free = tmp->content;
		tmp->content = content;
		if (to_free)
		{
			free (to_free);
			to_free = 0;
		}
		if (var->env_name)
		{
			free (var->env_name);
			var->env_name = 0;
		}
		return (-1);
	}
	return (0);
}

int	export_env_reassigned_check(t_var *var, char *name, char *content)
{
	t_envar	*tmp;
	int		i;

	tmp = var->envar;
	i = 0;
	while (tmp)
	{
		if (var->equal_env == 1)
		{
			i = export_env_reassignement(var, tmp, name, content);
			if (i == -1)
				return (-1);
		}
		if (var->equal_env == 0)
		{
			if (var->env_name)
			{
				free (var->env_name);
				var->env_name = 0;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
