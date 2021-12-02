#include "multipipes.h"

int	builtin_first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	for (int l = 0; l < var->cmd_nb + 1; l++)
		free (pipefd[l]);
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
	ft_putstr_fd("le bon test\n", 2);
	exit (0);
}

int	builtin_in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	for (int l = 0; l < var->cmd_nb + 1; l++)
		free (pipefd[l]);
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
	ft_putstr_fd("le bon test\n", 2);
	exit (0);
}

int	builtin_last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	close_fd(var);
	(pvar->builtin)[pvar->ret].func(var);
	for (int l = 0; l < var->cmd_nb + 1; l++)
		free (pipefd[l]);
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
	ft_putstr_fd("le bon test\n", 2);
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
