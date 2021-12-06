#include "multipipes.h"

void	free_builtin_cmd(t_var *var, t_pvar *pvar, int	**pipefd)
{
	free (pipefd);
	free (pvar->pids);
	free_split(pvar->path);
	free_envar(var->envar);
	free_envar(var->export);
	free(pvar->cmd);
	free(pvar->builtin);
	var->input = var->to_free;
	free_input(var);
	free(var->cd);
	rl_clear_history();
}

int	builtin_first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	int	l;

	l = -1;
	if (var->input->in_fd > 0)
		dup2(var->input->in_fd, STDIN_FILENO);
	if (var->input->out_fd > 0)
		dup2(var->input->out_fd, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	while (++l < var->cmd_nb + 1)
		free (pipefd[l]);
	free_builtin_cmd(var, pvar, pipefd);
	exit (0);
}

int	builtin_in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	int	l;

	l = -1;
	if (var->input->in_fd > 0)
		dup2(var->input->in_fd, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->out_fd > 0)
		dup2(var->input->out_fd, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	while (++l < var->cmd_nb + 1)
		free (pipefd[l]);
	free_builtin_cmd(var, pvar, pipefd);
	exit (0);
}

int	builtin_last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	int	l;

	l = -1;
	if (var->input->in_fd > 0)
		dup2(var->input->in_fd, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->out_fd > 0)
		dup2(var->input->out_fd, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	while (++l < var->cmd_nb + 1)
		free (pipefd[l]);
	free_builtin_cmd(var, pvar, pipefd);
	exit (0);
}

int	proceed_builtin_pipes(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (i == 0)
	{
		builtin_first_cmd(pvar, var, pipefd, i);
		return (0);
	}
	else if (i == pvar->cmd_nb - 1)
	{
		builtin_last_cmd(pvar, var, pipefd, i);
		return (0);
	}
	else
	{
		builtin_in_between_cmd(pvar, var, pipefd, i);
		return (0);
	}
}
