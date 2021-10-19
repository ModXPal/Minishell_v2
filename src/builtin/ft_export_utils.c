/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:07:27 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/19 15:25:35 by rcollas          ###   ########.fr       */
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

char	*export_name_equal_search(char *str, int *i, int *equal, char *name)
{
	while (str[(*i)])
	{
		if (str[(*i)] == '=')
		{
			(*equal) = 1;
			break ;
		}
		name[(*i)] = str[(*i)];
		(*i)++;
	}
	name[(*i)] = 0;
	return (name);
}

char	*export_content_search(int *i, char *str, char *content)
{
	int	j;

	j = 0;
	while (str[(*i)++])
	{
		content[j] = str[(*i)];
		j++;
	}
	content[j] = 0;
	return (content);
}
