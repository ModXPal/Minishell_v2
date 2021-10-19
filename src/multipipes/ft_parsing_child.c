/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:39:51 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/19 16:24:38 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_children(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->pipes->size_cmd_pipes)
	{
		if (i != var->pipes->i)
			close (var->pipes->tab_pipes[i][0]);
		if (var->pipes->i + 1 != i)
			close (var->pipes->tab_pipes[i][1]);
	}
}

void	close_fd(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->pipes->size_cmd_pipes)
	{
		close (var->pipes->tab_pipes[i][0]);
		close (var->pipes->tab_pipes[i][1]);
		i++;
	}
	close (var->pipes->fd[0]);
	close (var->pipes->fd[1]);
}

void	copy_fd_dup_child(t_var *var)
{
	close_fd_children(var);
	if (var->pipes->i == 0)
	{
		write(2, "1 :debut : pouet\n", 17);
		dup2(var->pipes->fd[0], STDIN_FILENO);
		dup2(var->pipes->tab_pipes[var->pipes->i + 1][1], STDOUT_FILENO);
		close(var->pipes->tab_pipes[var->pipes->i + 1][1]);
	}
	else if (var->pipes->i == var->pipes->size_cmd_pipes - 1)
	{
		write(2, "3 :fin : pouet\n", 15);
		dup2(var->pipes->tab_pipes[var->pipes->i][0], STDIN_FILENO);
		dup2(var->pipes->fd[1], STDOUT_FILENO);
		close(var->pipes->tab_pipes[var->pipes->i][0]);
	}
	else
	{
		write(2, "2 :Milieu : pouet\n", 18);
		dup2(var->pipes->tab_pipes[var->pipes->i][0], STDIN_FILENO);
		dup2(var->pipes->tab_pipes[var->pipes->i + 1][1], STDOUT_FILENO);
		close(var->pipes->tab_pipes[var->pipes->i + 1][1]);
	}
}

int	parsing_child(t_var *var)
{
	copy_fd_dup_child(var);
	ft_execve(var);
	return (0);
}
