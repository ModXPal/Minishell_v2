/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:48:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/25 17:24:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		EXIT_STATUS = WEXITSTATUS(status);
		if (EXIT_STATUS == 1234567890)
			EXIT_STATUS = 130;
	}
}

int	ft_exec(t_var *var, t_pvar *pvar, int pipe_fd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_dup(var, pipe_fd) == 1)
		{
			EXIT_STATUS = 1;
			return (EXIT_STATUS);
		}
		close_fd(var);
		if (execve(pvar->cmd, var->input->args, NULL) == -1)
		{
			ft_putstr_fd("minishell : ", 2);
			perror(pvar->cmd);
			free_split(pvar->path);
			EXIT_STATUS = 127;
			exit (EXIT_STATUS);
		}
	}
	waitpid(0, &status, WUNTRACED);
	handle_exit_status(status);
	close_fd(var);
	free_split(pvar->path);
	return (1);
}

int	handle_builtin(t_var *var, int pipe_fd[2], t_builtin *builtin, int ret)
{
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (ft_dup(var, pipe_fd) == 1)
		return (1);
	builtin[ret].func(var);
	close_fd(var);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	return (0);
}

int	ft_execve(t_var *var, t_builtin *builtin)
{
	t_pvar	pvar[1];
	int		ret;
	int		pipe_fd[2];

	ret = is_builtin(var->cmd, builtin);
	var->pvar = pvar;
	if (ret >= 0)
	{
		handle_builtin(var, pipe_fd, builtin, ret);
		return (EXIT_STATUS);
	}
	if (ret == -1)
		EXIT_STATUS = 1234567890;
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
	if (get_cmds(pvar, var) == 0)
		return (-1);
	if (ret < 0)
		ft_exec(var, pvar, pipe_fd);
	if (pvar->cmd && var->cmd[0] != '/' && var->cmd[0] != '.')
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	return (EXIT_STATUS);
}
