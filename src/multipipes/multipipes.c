/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/27 17:39:30 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	init_pipefd(t_pvar *pvar, int ***pipefd)
{
	int	i;

	i = -1;
	*pipefd = malloc(sizeof(int *) * (pvar->cmd_nb + 1));
	if (*pipefd == FAIL)
		return (0);
	while (++i < pvar->cmd_nb + 1)
	{
		(*pipefd)[i] = malloc(sizeof(int) * 2);
		if ((*pipefd)[i] == FAIL)
			return (0);
	}
	i = -1;
	while (++i < pvar->cmd_nb + 1)
	{
		if (pipe((*pipefd)[i]) == -1)
			return (0);
	}
	return (1);
}

int	init_pid(t_pvar *pvar)
{
	pvar->pids = (pid_t *)malloc(sizeof(pid_t) * (pvar->cmd_nb));
	if (pvar->pids == FAIL)
	{
		free(pvar->pids);
		return (0);
	}
	return (1);
}

void	init_pvar(t_pvar *pvar, t_var *var)
{
	pvar->cmd_nb = count_pipes(var);
	init_pid(pvar);
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
}

void	free_pipe(t_pvar *pvar, int **pipefd)
{
	int	i;

	i = -1;
	while (++i < pvar->cmd_nb)
		free(pipefd[i]);
	free (pipefd);
}

int	ft_multipipes(t_var *var)
{
	int		**pipefd;
	t_pvar	pvar[1];

	pipefd = NULL;
	init_pvar(pvar, var);
	init_pipefd(pvar, &pipefd);
	exec(pvar, var, pipefd, pvar->pids);
	free_pipe(pvar, pipefd);
	return (1);
}
