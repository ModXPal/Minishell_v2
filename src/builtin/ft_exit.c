/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:38 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/01 17:22:57 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exit_with_digits(t_var *var)
{
	int		i;

	i = 0;
	i = ft_atoi(var->input->args[1]);
	ft_putendl_fd("exit", 2);
	free_list(var);
	free_input(var);
	free_envar(var->envar);
	g_exit_status = i;
	exit (g_exit_status);
}

int	exit_with_too_many_arguments(t_var *var)
{
	if (split_len(var->input->args) > 2)
	{
		ft_putendl_fd("exit", 2);
		write(2, "minishell: ", 12);
		write(2, var->input->cmd, ft_strlen(var->input->cmd));
		ft_putendl_fd(": too many arguments", 2);
		free_list(var);
		free_input(var);
		free_envar(var->envar);
		g_exit_status = 1;
		exit (g_exit_status);
	}
	return (0);
}

int	exit_with_errors(t_var *var)
{
	int		i;

	i = 0;
	while (var->input->args[1][i])
	{
		if (!ft_isdigit(var->input->args[1][i]))
		{
			ft_putendl_fd("exit", 2);
			write (2, "minishell: ", 12);
			write(2, var->input->cmd, ft_strlen(var->input->cmd));
			write (2, ": ", 2);
			write(2, var->input->args[1], ft_strlen(var->input->args[1]));
			ft_putendl_fd(": numeric argument required", 2);
			free_list(var);
			free_input(var);
			free_envar(var->envar);
			g_exit_status = 1;
			exit (g_exit_status);
		}
		i++;
	}
	return (0);
}

int	exit_without_cmd(t_var *var)
{
	if (var->input->args[1] == 0)
	{
		ft_putendl_fd("exit", 2);
		free_list(var);
		free_input(var);
		free_envar(var->envar);
		g_exit_status = 0;
		exit (g_exit_status);
	}
	return (0);
}

int	ft_exit(t_var *var)
{
	int	i;

	i = 0;
	exit_without_cmd(var);
	exit_with_too_many_arguments(var);
	exit_with_errors(var);
	exit_with_digits(var);
	free_list(var);
	free_input(var);
	free_envar(var->envar);
	clear_history();
	return (0);
}
