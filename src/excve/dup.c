/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:17:35 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 18:17:36 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	dup_fd(t_var *var)
{
	if (var->input->IN_FD > 0)
		if (dup2(var->input->IN_FD, STDIN_FILENO) == -1)
			return (1);
	if (var->input->OUT_FD > 0)
		if (dup2(var->input->OUT_FD, STDOUT_FILENO) == -1)
			return (1);
	return (0);
}

int	dup_heredoc(t_var *var, int pipe_fd[2])
{
	if (var->input->heredoc)
	{
		if (pipe(pipe_fd) == -1)
			return (1);
		write (pipe_fd[1], var->input->heredoc,
			   ft_strlen(var->input->heredoc));
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (1);
		}
	}
	return (0);
}

int	ft_dup(t_var *var, int pipe_fd[2])
{
	if (dup_fd(var) == 1)
		return (1);
	if (dup_heredoc(var, pipe_fd) == 1)
		return (1);
	return (0);
}
