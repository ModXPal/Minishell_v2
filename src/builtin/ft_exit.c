/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:05:09 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 11:33:20 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exit_with_digits(t_var *var)
{
	int		i;

	i = 0;
	i = ft_atoi(var->input->args[1]);
	ft_putendl_fd("exit", 2);
	close(var->save_stdin);
	close(var->save_stdout);
	free(var->cd);
	free(var->builtin);
	free_input(var);
	free_envar(var->envar);
	free_envar(var->export);
	rl_clear_history();
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
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}

int	exit_with_errors(t_var *var)
{
	int		i;
	int		j;

	j = 0;
	check_if_integers_first(var);
	while (var->input->args[++j])
	{
		i = -1;
		while (var->input->args[j][++i])
		{
			if (exit_non_numeric_arguments(var, j, i) == 1)
				return (1);
		}
	}
	return (0);
}

int	exit_without_cmd(t_var *var)
{
	if (var->input->args[1] == 0)
	{
		ft_putendl_fd("exit", 2);
		close(var->save_stdin);
		close(var->save_stdout);
		free(var->cd);
		free(var->builtin);
		free_input(var);
		free_envar(var->envar);
		free_envar(var->export);
		rl_clear_history();
		exit (g_exit_status);
	}
	return (0);
}

int	ft_exit(t_var *var)
{
	int	i;

	i = 0;
	exit_without_cmd(var);
	if (exit_with_errors(var) == 1)
		return (1);
	if (exit_with_too_many_arguments(var) == 1)
		return (1);
	exit_with_digits(var);
	close(var->save_stdin);
	close(var->save_stdout);
	free(var->cd);
	free(var->builtin);
	free_input(var);
	free_envar(var->envar);
	free_envar(var->export);
	rl_clear_history();
	return (0);
}
