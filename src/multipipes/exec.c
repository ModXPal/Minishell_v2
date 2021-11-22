/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:16:49 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/07 15:47:07 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	check_access(t_pvar *pvar, int i)
{
	if (pvar->cmd == 0)
		return (0);
	if (i == -1)
	{
		if (access(pvar->cmd, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	else if (access(pvar->cmd, X_OK) == -1 && pvar->path[i + 1] == 0)
		return (0);
	else if (access(pvar->cmd, X_OK) == 0)
		return (1);
	return (-1);
}

int	check_relative_exec(char *str)
{
	if (ft_strncmp(str, "./", 2) == 0)
		return (1);
	if (ft_strncmp(str, "../", 3) == 0)
		return (2);
	return (0);
}

int	get_prog_path(t_pvar *pvar, t_var *var)
{
	if (check_relative_exec(var->input->cmd) == 1)
	{
		pvar->cmd = &(var->input->cmd[2]);
		return (0);
	}
	else if (check_relative_exec(var->input->cmd) == 2)
	{
		pvar->cmd = var->input->cmd;
		return (0);
	}
	return (1);
}

int	executable_error(t_var *var, t_pvar *pvar)
{
	if (access(pvar->cmd, X_OK) == -1)
	{
		write (2, "minishell: ", 11);
		perror(&var->cmd[2]);
		EXIT_STATUS = 127;
		return (0);
	}
	return (1);
}

int	check_input(t_pvar *pvar, t_var *var)
{
	if (get_prog_path(pvar, var) == 0)
	{
		if (check_access(pvar, -1) == SUCCESS)
			return (1);
		else if (check_access(pvar, -1) == FAIL)
			return (executable_error(var, pvar));
	}
	if (var->input->cmd[0] == '\0')
	{
		pvar->cmd = var->input->cmd;
		return (cmd_not_found(var));
	}
	if (var->input->cmd[0] == '/')
	{
		pvar->cmd = var->input->cmd;
		if (check_access(pvar, -1) == SUCCESS)
			return (1);
		else if (check_access(pvar, -1) == FAIL)
		{
			free_split(pvar->path);
			return (no_such_file(var));
		}
	}
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
			break ;
		else if (check_access(pvar, i) == FAIL)
		{
			free_split(pvar->path);
			free(pvar->cmd);
			return (cmd_not_found(var));
		}
		free(pvar->cmd);
	}
	return (1);
}

int	exec_execution(t_var *var, pid_t *pids, int **pipefd, t_pvar *pvar)
{
	int	i;

	i = -1;
	while (++i < pvar->cmd_nb)
	{
		if (i > 0)
			var->input = var->input->next;
		pvar->ret = is_builtin(var->input->cmd, pvar->builtin);
		if (pvar->ret == 6)
			return (0);
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed:");
			return (1);
		}
		if (pids[i] == 0)
		{
			if (pvar->ret >= 0)
				proceed_builtin_pipes(pvar, var, pipefd, i);
			else
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
	status = 0;
	if (exec_execution(var, pids, pipefd, pvar) == 1)
		return (1);
	close_pipes(pvar, pipefd);
	close_fd(var);
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, WUNTRACED);
	multipipes_signal_handling(status);
	free(pids);
	var->input = start;
	free_split(pvar->path);
	return (EXIT_STATUS);
}
