/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fct_exec_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:56:50 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 17:56:51 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	fork_exec_execuction(pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] == -1)
	{
		perror("Fork failed:");
		return (1);
	}
	return (0);
}

void	free_pvar_exec(t_pvar *pvar)
{
	if (pvar->cmd)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
}

int	child_exec_execution(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (pvar->ret >= 0)
		proceed_builtin_pipes(pvar, var, pipefd, i);
	else
		proceed_pipes(pvar, var, pipefd, i);
	return (0);
}

int	exec_execution_before_fork(t_var *var, int i, t_pvar *pvar)
{
	dup2(var->save_stdin, STDIN_FILENO);
	dup2(var->save_stdout, STDOUT_FILENO);
	if (i > 0)
		var->input = var->input->next;
	pvar->ret = is_builtin(var->input->cmd, pvar->builtin);
	return (0);
}
