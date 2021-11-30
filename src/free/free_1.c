/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:10:26 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 11:20:49 by                  ###   ########.fr       */
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

void	free_input_list(t_input *input)
{
	t_input	*tmp;

	tmp = NULL;
	if (input)
	{
		while (input)
		{
			if (input->next)
				tmp = input->next;
			else
				tmp = NULL;
			if (input->args)
				free_split(input->args);
			free (input);
			input = NULL;
			input = tmp;
		}
	}
}

void	free_cd_path(t_var *var)
{
	if (var->cd->cdpath)
	{
		free(var->cd->cdpath);
		var->cd->cdpath = 0;
	}
}
