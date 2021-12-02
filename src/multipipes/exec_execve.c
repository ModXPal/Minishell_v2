/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:50 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/02 15:17:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	int	pipe_heredoc[2];

	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else if (var->input->heredoc)
	{
		pipe(pipe_heredoc);
		dup_heredoc(var, pipe_heredoc);
	}
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	if (execve(pvar->cmd, var->input->args, var->env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pvar->cmd);
		free_with_pvar(var, pvar);
		EXIT_STATUS = 127;
		exit (EXIT_STATUS);
	}
	return (1);
}

int	in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	int pipe_heredoc[2];

	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else if (var->input->heredoc)
	{
		pipe(pipe_heredoc);
		dup_heredoc(var, pipe_heredoc);
	}
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	if (execve(pvar->cmd, var->input->args, var->env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pvar->cmd);
		free_with_pvar(var, pvar);
		EXIT_STATUS = 127;
		exit (EXIT_STATUS);
	}
	return (1);
}

int	last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	int pipe_heredoc[2];

	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else if (var->input->heredoc)
	{
		pipe(pipe_heredoc);
		dup_heredoc(var, pipe_heredoc);
	}
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	if (execve(pvar->cmd, var->input->args, var->env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pvar->cmd);
		free_with_pvar(var, pvar);
		EXIT_STATUS = 127;
		exit (EXIT_STATUS);
	}
	return (1);
}

void	proceed_pipes(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (i == 0)
	{
		first_cmd(pvar, var, pipefd, i);
	}
	else if (i == pvar->cmd_nb - 1)
	{
		//if (get_cmds(pvar, var) == FAIL)
		//	exit (1);
		last_cmd(pvar, var, pipefd, i);
	}
	else
	{
		//if (get_cmds(pvar, var) == FAIL)
		//	exit (1);
		in_between_cmd(pvar, var, pipefd, i);
	}
}
