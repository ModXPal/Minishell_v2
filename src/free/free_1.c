/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:10:26 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/22 14:32:05 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_list(t_var *var)
{
	t_list	*tmp;

	if (var->list)
	{
		while (var->list)
		{
			tmp = var->list->next;
			free(var->list->content);
			free(var->list);
			var->list = tmp;
		}
	}
}

void	free_split(char **split_str)
{
	int	i;

	i = -1;
	if (split_str)
	{
		while (split_str[++i])
			free(split_str[i]);
		free(split_str);
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

void	free_input(t_var *var)
{
	int	i;

	i = -1;
	if (var && var->input)
	{
		// while ((var->input->args)[++i])
		// 	free((var->input->args)[i]);
		// free(var->input);
	}
}
