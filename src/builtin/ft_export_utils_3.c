/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:27:38 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/25 18:34:47 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

char *env_name_init(t_var *var, char *args)
{
	int len;
	int i;
	char *name;
	
	i = 0;
	len = export_name_len(var, args);
	name = ((char *)ft_calloc(sizeof(char), (len + 1)));
	if (!name)
		return (0);
	while (i < len)
	{
		name[i] = args[i];
		i++;
	}
	return (name);
}

char *env_content_init(t_var *var, char *args, int j)
{
	int i;
	int k;
	char *name;
	
	k = export_name_len(var, args) + 1;
	i = 0;
	name = ((char *)ft_calloc(sizeof(char), (j + 1)));
	if (!name)
		return (0);
	while (args[k])
	{
		name[i] = args[k];
		i++;
		k++;
	}
	return (name);
}

int name_already_exist(t_var *var, char *args, int flag)
{
	int		i;
	int		j;
	t_envar	*tmp;
	char	*check;

	i = 0;
	if (flag == EXPORT)
		tmp = var->export;
	else if (flag == ENV)
		tmp = var->envar;
	j = 0;
	check = ft_strdup(args);
	while (check[i])
	{
		if (check[i] == '=')
		{
			check[i] = '\0';
			var->equal_env = 1;
			break ;
		}
		i++;
	}
	while (ft_strcmp(tmp->name, check) != 1)
	{
		if (tmp->next != 0 && tmp)
			tmp = tmp->next;
		if (tmp->next == 0)
		{
			free (check);
			return(j);
		}
	}
	if (ft_strcmp(tmp->name, check) == 1)
	{
		j = 1;	
	}
	free (check);
	return (j);
}
