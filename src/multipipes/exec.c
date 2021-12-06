/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:41:37 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 10:32:24 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	check_access_check_input(t_pvar *pvar, t_var *var)
{
	if (var->input->cmd[0] == '/')
	{
		pvar->cmd = ft_strdup(var->input->cmd);
		if (check_access(pvar, -1) == SUCCESS)
			return (1);
		else if (check_access(pvar, -1) == FAIL)
			return (no_such_file(var));
	}
	return (151);
}

int	check_input(t_pvar *pvar, t_var *var)
{
	DIR	*dir;
	int	i;

	i = 0;
	if (get_prog_path(pvar, var) == 0)
	{
		dir = opendir(pvar->cmd);
		if (check_access(pvar, -1) == SUCCESS && dir == NULL)
			return (1);
		else if (check_access(pvar, -1) == FAIL || dir != NULL)
		{
			closedir(dir);
			return (executable_error(var, pvar));
		}
		closedir(dir);
	}
	if (!var->input->cmd || var->input->cmd[0] == '\0')
	{
		pvar->cmd = ft_strdup("");
		return (cmd_not_found(var));
	}
	i = check_access_check_input(pvar, var);
	if (i != 151)
		return (i);
	return (-1);
}

int	get_cmds(t_pvar *pvar, t_var *var)
{
	int		i;
	int		ret;

	i = -1;
	ret = check_input(pvar, var);
	if (ret == 1)
		return (1);
	else if (ret == 0)
		return (0);
	while (pvar->path[++i])
	{
		pvar->cmd = ft_strjoin(pvar->path[i], var->input->cmd);
		if (check_access(pvar, i) == SUCCESS)
			return (1);
		else if (check_access(pvar, i) == FAIL)
			return (cmd_not_found(var));
		free(pvar->cmd);
	}
	return (no_such_file(var));
}

int	exec_execution(t_var *var, pid_t *pids, int **pipefd, t_pvar *pvar)
{
	int	i;

	i = -1;
	var->to_free = var->input;
	while (++i < pvar->cmd_nb)
	{
		exec_execution_before_fork(var, i, pvar);
		if (pvar->ret == 6)
			return (0);
		if (pvar->ret == -1 && get_cmds(pvar, var) == FAIL)
		{
			free (pvar->cmd);
			pvar->cmd = NULL;
			continue ;
		}
		if (fork_exec_execuction(pids, i) == -1)
			return (1);
		if (pids[i] == 0)
		{
			child_exec_execution(pvar, var, pipefd, i);
			break ;
		}
		free_pvar_exec(pvar);
	}
	return (0);
}

int	exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids)
{
	int		i;
	int		status;
	t_input	*start;

	start = var->input;
	status = 0;
	if (exec_execution(var, pids, pipefd, pvar) == 1)
		return (1);
	close_pipes(pvar, pipefd);
	close_fd(var);
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, 0);
	multipipes_signal_handling(status);
	free(pids);
	var->input = start;
	free_split(pvar->path);
	if (pvar->cmd)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	pipefd = NULL;
	return (g_exit_status);
}
