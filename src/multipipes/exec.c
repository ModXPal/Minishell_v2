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

int	cmd_not_found(t_var *var, t_pvar *pvar)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": command not found\n", 20);
	free(pvar->cmd);
	EXIT_STATUS = 127;
	return (0);
}

int	no_such_file(t_var *var)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": no such file or directory\n", 28);
	return (0);
}

int	get_cmds(t_pvar *pvar, t_var *var)
{
	int		i;

	i = -1;
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
	while (pvar->path[++i])
	{
		pvar->cmd = ft_strjoin(pvar->path[i], var->input->cmd);
		if (check_access(pvar, i) == SUCCESS)
			break ;
		else if (check_access(pvar, i) == FAIL)
		{
			free_split(pvar->path);
			return (cmd_not_found(var, pvar));
		}
		free(pvar->cmd);
	}
	return (1);
}

int	first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	if (execve(pvar->cmd, var->input->args, NULL) == -1)
		perror("Execve failed:");
	return (1);
}

int	in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
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
	execve(pvar->cmd, var->input->args, NULL);
	return (1);
}

int	last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
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

int	builtin_first_cmd(t_pvar *pvar, t_var *var, int	**pipefd, int i)
{
	(void)i;
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	(pvar->builtin)[pvar->ret].func(var);
	exit (0);
}

int	builtin_in_between_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	(void)i;
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	else
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	(pvar->builtin)[pvar->ret].func(var);
	exit (0);
}

int	builtin_last_cmd(t_pvar *pvar, t_var *var, int **pipefd, int i)
{
	(void)i;
	if (var->input->IN_FD > 0)
		dup2(var->input->IN_FD, STDIN_FILENO);
	else
		dup2(pipefd[i][0], STDIN_FILENO);
	if (var->input->OUT_FD > 0)
		dup2(var->input->OUT_FD, STDOUT_FILENO);
	close_pipes(pvar, pipefd);
	(pvar->builtin)[pvar->ret].func(var);
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

int	exec_execution(t_var *var, pid_t *pids, int **pipefd, t_pvar *pvar)
{
	int	i;

	i = -1;
	while (++i < pvar->cmd_nb)
	{
		if (i > 0)
			var->input = var->input->next;
		pvar->ret = is_builtin(var->input->cmd, pvar->builtin);
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
			else proceed_pipes(pvar, var, pipefd, i);
			if (var->input->IN_FD > 0)
				close(var->input->IN_FD);
			if (var->input->OUT_FD > 0)
				close(var->input->OUT_FD);
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
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, WUNTRACED);
	multipipes_signal_handling(status);
	free(pids);
	var->input = start;
	free_split(pvar->path);
	return (EXIT_STATUS);
}
