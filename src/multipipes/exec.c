/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:16:49 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/27 17:37:14 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	dup2(pipefd[i][0], STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	execve(pvar->cmd, var->input->args, NULL);
	return (1);
}

int	last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	dup2(pipefd[i][0], STDIN_FILENO);
	close_pipes(pvar, pipefd);
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

int	exec_execution(t_var *var, pid_t *pids, int **pipefd, t_pvar *pvar)
{
	int	i;

	i = -1;
	while (++i < pvar->cmd_nb)
	{
		if (i > 0)
			var->input = var->input->next;
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed:");
			return (1);
		}
		if (pids[i] == 0)
		{
			proceed_pipes(pvar, var, pipefd, i);
			break ;
		}
	}
	return (0);
}

int	exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids)
{
	int		i;
	int		status;
	t_input	*start;

	start = var->input;
	if (exec_execution(var, pids, pipefd, pvar) == 1)
		return (1);
	close_pipes(pvar, pipefd);
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, 0);
	//free(pids);
	var->input = start;
	free_split(pvar->path);
	return (1);
}
