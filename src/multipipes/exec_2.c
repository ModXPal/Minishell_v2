/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:21:02 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/27 17:23:26 by vbachele         ###   ########.fr       */
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
	while (pvar->path[++i])
	{
		pvar->cmd = ft_strjoin(pvar->path[i], var->input->cmd);
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
