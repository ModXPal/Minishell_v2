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
	printf("pipe[%d] = %d\n", i - 1, (*pipefd)[i - 1][0]);
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

void	init_pvar(t_pvar *pvar, t_var *var, t_builtin *builtin)
{
	pvar->cmd_nb = var->cmd_nb;
	pvar->cmd = NULL;
	pvar->builtin = builtin;
	init_pid(pvar);
	pvar->path = get_binaries_path(var);
	pvar->ret = 0;
	add_slash(pvar);
}

void	free_pipe(t_pvar *pvar, int **pipefd)
{
	int	i;

	i = -1;
	while (++i < pvar->cmd_nb + 1)
		free(pipefd[i]);
	free (pipefd);
}

int	ft_multipipes(t_var *var, t_builtin *builtin)
{
	int		**pipefd;
	t_pvar	pvar[1];

	pipefd = NULL;
	init_pvar(pvar, var, builtin);
	init_pipefd(pvar, &pipefd);
	exec(pvar, var, pipefd, pvar->pids);
	free_pipe(pvar, pipefd);
	return (1);
}
