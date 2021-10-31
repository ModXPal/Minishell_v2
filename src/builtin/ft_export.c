/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:45:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/29 16:18:33 by vbachele         ###   ########.fr       */
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

void	export_execution(t_var *var, char *args)
{
	int		i;
	int		equal;
	char	*name;
	char	*content;
	int		j;

	i = 0;
	equal = 0;
	content = 0;
	j = 0;
	name = 0;
	if (unset_export_error_handling(var, args) != -1)
	{
		name = ((char *)malloc(sizeof(char) * (export_name_len(args) + 1)));
		name = export_name_equal_search(args, &i, &equal, name);
		if (equal == 1)
			j = ft_strlen(args) - export_name_len(args);
		if (j > 0 && equal == 1)
		{
			content = ((char *) malloc(sizeof(char) * (j + 1)));
			content = export_content_search(&i, args, content);
		}
		i = export_env_reassigned_check(var, name, content, equal);
		if (equal == 1 && i != -1)
			export_env_insert(var, name, content);
		if (export_export_reassigned_check(var, name, content, equal) != -1)
			cmd_export_insert(var, name, content, equal);
	}
	if (name)
	{
		free (name);
	}
	if (content && equal == 1)
	{
		free (content);
	}
}

int	ft_export(t_var *var)
{
	int		j;

	if (cmd_export_alone(var) == 1)
		return (0);
	j = 1;
	while (var->input->args[j])
	{
		export_execution(var, var->input->args[j]);
		j++;
	}
	return (0); // bien penser a free ici
}
