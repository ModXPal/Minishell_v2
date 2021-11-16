/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:50 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 11:57:51 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	if (execve(pvar->cmd, var->input->args, NULL) == -1)
		perror("Execve failed:");
	return (1);
}

int	in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	execve(pvar->cmd, var->input->args, NULL);
	return (1);
}

int	last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	if (execve(pvar->cmd, var->input->args, NULL) == -1)
		perror("Execve failed:");
	return (1);
}

void	proceed_pipes(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (i == 0)
	{
		if (get_cmds(pvar, var) == FAIL)
			exit (1);
		first_cmd(pvar, var, pipefd, i);
	}
	else if (i == pvar->cmd_nb - 1)
	{
		if (get_cmds(pvar, var) == FAIL)
			exit (1);
		last_cmd(pvar, var, pipefd, i);
	}
	else
	{
		if (get_cmds(pvar, var) == FAIL)
			exit (1);
		in_between_cmd(pvar, var, pipefd, i);
	}
}
