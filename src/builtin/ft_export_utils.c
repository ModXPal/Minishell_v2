/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:27 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/29 16:03:17 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_export_alone(t_var *var)
{
	t_envar	*tmp2;

	tmp2 = var->export;
	if (var->input->args[1] == 0)
	{
		while (tmp2)
		{
			if (tmp2->content == 0)
			{
				printf("export %s\n", tmp2->name);
			}
			if (tmp2->content != 0)
			{
				printf("export %s=\"%s\"\n", tmp2->name, tmp2->content);
			}
			tmp2 = tmp2->next;
		}
		return (1);
	}
	return (0);
}

char	*export_name_equal_search(t_var *var, char *str, int *i, int *equal)
{
	while (str[(*i)])
	{
		if (str[(*i)] == '=')
		{
			(*equal) = 1;
			break ;
		}
		var->name[(*i)] = str[(*i)];
		(*i)++;
	}
	var->name[(*i)] = 0;
	return (var->name);
}

char	*export_content_search(t_var *var, int *i, char *str)
{
	int	j;

	j = 0;
	while (str[(*i)++])
	{
		var->content[j] = str[(*i)];
		j++;
	}
	var->content[j] = 0;
	return (var->content);
}

int	cmd_export_insert(t_var *var, int equal)
{
	t_envar	*new;
	t_envar	*tmp2;
	int		pos;

	tmp2 = var->export;
	if (equal == 0)
	{
		new = ft_envar_new(var->name, 0);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	else
	{
		new = ft_envar_new(var->name, var->content);
		pos = ft_envarsize(tmp2);
		envar_insert(&var->export, new, pos);
	}
	// if (name)
	// {
	// 	free (name);
	// }
	// if (content)
	// {
	// 	free (content);
	// }
	return (0);
}
