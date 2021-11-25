/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:04:04 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/25 18:30:45 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_name_len(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var->equal_env = 1;
			break ;
		}
		i++;
	}
	return (i);
}

int	export_error_no_equal(t_var *var, char *content)
{
	int	j;

	j = 0;
	while (content[j])
	{
		if (content[j] == '=')
			break ;
		else if (ft_isalnumqual(content[j]) == 0)
		{
			unset_error_export_message(var, content);
			return (-1);
		}
		j++;
	}
	return (0);
}

int	export_error_handling(t_var *var, char *content)
{
	int		i;

	i = 1;
	if (var->input->args[1] == 0 || content[0] == 0)
		return (-1);
	if (content[0] == 0)
		return (-1);
	if (content[0] == '=')
	{
		unset_error_export_message(var, content);
		return (-1);
	}
	if (ft_isdigit(content[0]) || content[0] == 0)
	{
		unset_error_export_message(var, content);
		return (-1);
	}
	if (export_error_no_equal(var, content) == -1)
		return (-1);
	return (0);
}

int	export_export_reassigned_check(t_var *var, char *name,
					char *content, int export_already_exist)
{
	t_envar	*tmp;
	char	*to_free;

	tmp = var->export;
	to_free = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 1 && var->equal_env == 1)
		{
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

int	export_env_reassigned_check(t_var *var, char *name, char *content)
{
	t_envar	*tmp;
	char 	*to_free;
	char 	*to_free2;

	tmp = var->envar;
	to_free = 0;
	to_free2 = 0;
	while (tmp)
	{
		if (var->equal_env == 1)
		{
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
					return (-1);
				}
				return (-1);
			}
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
