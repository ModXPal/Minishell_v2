/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:41:31 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/04 13:56:23 by rcollas          ###   ########.fr       */
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
		EXIT_STATUS = 1;
		exit (EXIT_STATUS);
	}
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
