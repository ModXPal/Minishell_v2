/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:41:31 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 12:09:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env_error_handling(t_var *var)
{
	if (var->input->args[1] != 0)
	{
		write(2, var->input->args[0], ft_strlen(var->input->args[0]));
		write(2, ": ", 2);
		write(2, var->input->args[1], ft_strlen(var->input->args[1]));
		write(2, ": No such file or directory\n", 29);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (var->env == FAIL || var->envar == FAIL)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}

int	ft_env(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	if (env_error_handling(var) == 1)
		return (g_exit_status);
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
