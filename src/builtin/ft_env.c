/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:41:31 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/01 17:21:48 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	if (var->env == FAIL || var->envar == FAIL)
	{
		printf("Error\n");
		g_exit_status = 1;
		exit (g_exit_status);
	}
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	exit (g_exit_status);
}
