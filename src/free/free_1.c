/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:04:19 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/08 17:03:19 by                  ###   ########.fr       */
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

void	ft_free(void *to_free)
{
	free(to_free);
	to_free = NULL;
}

void	free_with_pvar(t_var *var, t_pvar *pvar)
{
	free_split(pvar->path);
	free_envar(var->envar);
	free_envar(var->export);
	free(pvar->cmd);
	free(pvar->builtin);
	free(var->cd);
	free_list(var);
	rl_clear_history();
}
