/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:44:30 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 12:41:42 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_split(char **split_str)
{
	int	i;

	i = -1;
	if (split_str && *split_str)
	{
		while (split_str[++i])
		{
			free(split_str[i]);
			split_str[i] = NULL;
		}
		free(split_str);
		split_str = NULL;
	}
}

void	free_envar(t_envar *envar)
{
	t_envar	*tmp;

	if (envar)
	{
		while (envar)
		{
			tmp = envar->next;
			free(envar->name);
			free(envar->content);
			free(envar);
			envar = tmp;
		}
	}
}

void	free_pvar(t_pvar *pvar)
{
	if (pvar->cmd)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	if (pvar->path)
		free_split(pvar->path);
}

void	free_input(t_var *var)
{
	if (var && var->input)
		free_input_list(var->input);
	if (var && var->trim_expand)
	{
		free(var->trim_expand);
		var->trim_expand = NULL;
	}
}

void	free_all(t_var *var)
{
	free(var->cmd);
	var->cmd = NULL;
	free_input(var);
	free_pvar(var->pvar);
}
