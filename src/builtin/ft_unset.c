/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:06 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 15:08:34 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(t_var *var)
{
	t_envar *tmp;
	int pos;
	
	pos = 0;
	tmp = var->envar;
	var->cmd = &(var->cmd[6]);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var->cmd) == 1)
		{
			pos = ft_envar_position(var->envar, tmp->name);
			envar_remove(&var->envar, pos);
		}
		tmp = tmp->next;
	}
	return (0);
}
