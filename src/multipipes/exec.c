/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:16:49 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/25 13:14:30 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	close_pipes(t_pvar *pvar, int **pipefd)
{
	int	j;

	j = -1;
	while (++j < pvar->cmd_nb + 1)
	{
		if (close(pipefd[j][0]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
		if (close(pipefd[j][1]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
	}
	return (1);
}

int	check_access(t_pvar *pvar, int i)
{
	if (pvar->cmd == 0)
		return (0);
	if (access(pvar->cmd, X_OK) == -1 && pvar->path[i + 1] == 0)
		return (0);
	else if (access(pvar->cmd, X_OK) == 0)
		return (1);
	return (-1);
}

int	cmd_not_found(t_var *var, t_pvar *pvar)
{
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": command not found\n", 20);
	free(pvar->cmd);
	return (0);
}

int	get_cmds(t_pvar *pvar, t_var *var)
{
	int		i;

	i = -1;
	printf("var->input->cmd = %s\n", var->input->cmd);
	while (pvar->path[++i])
	{
		pvar->cmd = ft_strjoin(pvar->path[i], var->input->cmd);
		printf("pvar cmd = %s\n", pvar->cmd);
		if (check_access(pvar, i) == SUCCESS)
			break ;
		else if (check_access(pvar, i) == FAIL)
			return (cmd_not_found(var, pvar));
		free(pvar->cmd);
	}
	return (1);
}

int	first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	if (execve(pvar->cmd, var->input->args, NULL) == -1)
		perror("Execve failed:");
	return (1);
}

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

int	exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids)
{
	int	i;
	int	status;
	t_input	*start;

	i = -1;
	start = var->input;
	while (++i < pvar->cmd_nb)
	{
		if (i > 0)
			var->input = var->input->next;
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed:");
			return (0);
		}
		if (pids[i] == 0)
		{
			proceed_pipes(pvar, var, pipefd, i);
			break ;
		}
	}
	close_pipes(pvar, pipefd);
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, 0);
	//free(pids);
	var->input = start;
	free_split(pvar->path);
	return (1);
}
