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

int env_error_handling(t_var *var)
{
	if (var->input->args[1] != 0)
	{
		write(2, var->input->args[0], ft_strlen(var->input->args[0]));
		write(2, ": ", 2);
		write(2, var->input->args[1], ft_strlen(var->input->args[1]));
		write(2, ": No such file or directory\n", 29);
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	if (var->env == FAIL || var->envar == FAIL)
	{
		printf("Error\n");
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	return (0);
}

int	ft_env(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	if (env_error_handling(var) == 1)
		return (EXIT_STATUS);
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	EXIT_STATUS = 0;
	return (EXIT_STATUS);
}
