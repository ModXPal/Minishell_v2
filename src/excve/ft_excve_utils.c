/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:54:56 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/08 17:29:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_builtin(t_var *var, int pipe_fd[2], t_builtin *builtin, int ret)
{
	if (ft_dup(var, pipe_fd) == 1)
		return (1);
	builtin[ret].func(var);
	close_fd(var);
	dup2(var->save_stdout, STDOUT_FILENO);
	dup2(var->save_stdin, STDIN_FILENO);
	return (0);
}

int	check_cmd(t_var *var)
{
	if (var->input->cmd == NULL && (var->input->in_fd > 0
			|| var->input->out_fd > 0 || var->input->heredoc))
		return (-1);
	if (var->input->in_fd == -1 || var->input->out_fd == -1)
		return (-1);
	return (0);
}

int	check_ret(int ret, t_var *var, t_builtin *builtin, int *pipe_fd)
{
	if (ret >= 0)
	{
		handle_builtin(var, pipe_fd, builtin, ret);
		return (g_exit_status);
	}
	if (ret == -1)
		g_exit_status = 1234567890;
	return (-216);
}
