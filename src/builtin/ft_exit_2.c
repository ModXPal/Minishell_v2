/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:50:01 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 11:23:35 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exit_non_numeric_arguments(t_var *var, int j, int i)
{
	if (!ft_isdigit(var->input->args[j][i]))
	{
		ft_putendl_fd("exit", 2);
		write (2, "minishell: ", 12);
		write(2, var->input->cmd, ft_strlen(var->input->cmd));
		write (2, ": ", 2);
		write(2, var->input->args[1], ft_strlen(var->input->args[1]));
		ft_putendl_fd(": numeric argument required", 2);
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	return (0);
}

int	free_check_if_integers_first(t_var *var)
{
	free(var->cd);
	free(var->builtin);
	free_input(var);
	free_envar(var->envar);
	free_envar(var->export);
	rl_clear_history();
}

int	check_if_integers_first(t_var *var)
{
	int	j;
	int	i;

	j = 1;
	i = -1;
	while (var->input->args[j][++i])
	{
		if (!ft_isdigit(var->input->args[j][i]))
		{
			ft_putendl_fd("exit", 2);
			write (2, "minishell: ", 12);
			write(2, var->input->cmd, ft_strlen(var->input->cmd));
			write (2, ": ", 2);
			write(2, var->input->args[1], ft_strlen(var->input->args[1]));
			ft_putendl_fd(": numeric argument required", 2);
			free_check_if_integers_first(var);
			EXIT_STATUS = 1;
			exit (EXIT_STATUS);
		}
	}
	return (0);
}
