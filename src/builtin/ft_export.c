/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:24:10 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/12 18:30:36 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int		incremente_pos(int *pos)
// {
// 	(*pos)++;
// }

// incremente_pos(&pos);

int	cmd_export_alone(t_var *var)
{
	t_envar *tmp2;
	t_list	*tmp;
	
	tmp = var->list;
	tmp2 = var->export;
	
	if (tmp->next == 0)
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
	}
	return (0);
}

int	export_env_reassigned_check(t_var *var, char *name, char *content, int equal)
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

int	export_export_reassigned_check(t_var *var, char *name, char *content, int equal)
{
	t_envar	*tmp;

	tmp = var->export;
	(void) equal;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 1)
		{
			tmp->content = content;
			return (-1);
		}
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
	t_envar *new;
	t_envar *tmp2;
	t_list	*tmp;
	int		pos;
	char	*str;
	
	tmp = var->list;
	str = NULL;
	tmp2 = var->export;
	if (tmp->next != FALSE)
		str = tmp->next->content;
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
	
	int		j;
	char	*name;
	char	*content;
	int		equal;
	char	*str;
	t_list	*tmp;
	// t_envar	*tmp2;

	j = 0;
	i = 0;
	equal = 0;
	tmp = var->list;
	name = 0;
	cmd_export_alone(var);
	if (tmp->next != 0)
	{
		str = tmp->next->content;
		name = malloc(sizeof(ft_strlen(str)));
		content = malloc(sizeof(ft_strlen(str)));
		while (str[i])
		{
			if (str[i] == '=')
			{
				equal = 1;
				break ;
			}
			name[i] = str[i];
			i++;
		}
		while (str[i++])
		{
			content[j] = str[i];
			j++;
		}
		export_env_reassigned_check(var, name, content, equal);
		if (export_export_reassigned_check(var, name, content, equal) == -1)
			return (-1);
		if (equal == 1)
			export_env_insert(var, name, content);
		// tmp2 = var->export;
		// while(tmp2)
		// {
		// 	if (ft_strcmp(name, tmp2->content) == 1)
		// 		return (-1);
		// 	tmp2 = tmp2->next;
		// }
		cmd_export_insert(var, name, content, equal);
	}
	return (0);
}
